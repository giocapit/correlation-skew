#include "JuBasketOptionPrice.hpp"
#include "ProcessBiVariateLognormalAbstract.hpp"
#include <cmath>


JuBasketOptionPricer::JuBasketOptionPricer(const BasketOption *option, Process *process, double riskFreeRate): BSBasketOptionPricer(option, process, riskFreeRate)
{
	strike = this->option->getStrike();
	Basket* underlyingBasket = 
		dynamic_cast<Basket*>(((BasketOption*) option)->getUnderlying());
	sigma1 = 
		(dynamic_cast<ProcessBiVariateLognormalAbstract*> (processo))->getSigma1();
	sigma2 = 
		(dynamic_cast<ProcessBiVariateLognormalAbstract*> (processo))->getSigma2();
	rho = 
		(dynamic_cast<ProcessBiVariateLognormalAbstract*> (processo))->getRho();
	w1 = underlyingBasket->get_w1();
	w2 = underlyingBasket->get_w2();
	multiplier = underlyingBasket->getMultiplier();

	U1 = multiplier;
	U2 = pow(multiplier,2) * (pow(w1,2) * exp(pow(sigma1,2)) + pow(w2,2) * exp(pow(sigma2,2)) + w1*w2 * exp(sigma1 * sigma2 * rho));

	m = 2 * log(U1) - 0.5 * log(U2);
	s = log(U2) - 2 * log(U1);

	printf("s è % .5e\n ", s);
};

double JuBasketOptionPricer::getOptionPrice()
{

	double dU2 = pow(multiplier,2) * (pow(w1,2) + pow(w2,2) + rho * w1*w2);
	double d2U2 = pow(multiplier,2) * (pow(w1,2) + pow(w2,2) + pow(rho,2) * w1*w2);
	double d3U2 = pow(multiplier,2) * (pow(w1,2) + pow(w2,2) + pow(rho,3) * w1*w2);
	double a1 = - dU2/(2 * U2);
	double a2 = 2 * a1 - d2U2/(2*U2);
	double a3 = 6 * a1 * a2 - 4 * pow(a1,3) - d3U2/(2*U2);

	double b1 = 0.5 * (pow(w1,3) + pow(w1,2) * w2 * (2 * rho + pow(rho,2)) + w1 * pow(w2,2) * (2 * rho + pow(rho,2)) + pow(w2,3));
	double b2 = pow(a1,2) - 0.5 * a2;

	double c1 = - a1 * b1;
	double k1 = 8 * (pow(w1,4) + 
			2 * pow(w1,3) * w2 * (rho + pow(rho,2)) + 
			2 * pow(w1,2) * pow(w2,2) * (rho + pow(rho,2) + pow(rho,3)) + 
			2 * w1 * pow(w2,3) * (rho + pow(rho,2)) + 
			pow(w2,4)) + 2 * dU2 * d2U2 ;
	double k2 =  6 * (pow(w1,4) + 
			4 * pow(w1,3) * w2 * rho + 
			6 * pow(w1,2) * pow(w2,2) * pow(rho,2) + 
			4 * w1 * pow(w2,3) * rho + 
			pow(w2,4));
	double c2 = (1/(144 * pow(multiplier,4))) * (9 * k1 + 4 * k2);

	double q1 = 6 * (pow(w1,3) +
			pow(w1,2) * w2 * (rho + pow(rho,2) + pow(rho,3)) +
			w1 * pow(w2,2) * (rho + pow(rho,2) + pow(rho,3)) +
			pow(w2,3));
	double q2 = 8 * (pow(w1,3) +
			3 * pow(w1,2) * w2 * pow(rho,2) +
			3 * w1 * pow(w2,2) * pow(rho,2) +
			pow(w2,3));
	double c3 = (1/(48 * pow(multiplier,3))) * (4 * q1 + q2);
	double c4 = a1 * a2 - 2/3 * pow(a1,3) - a3/6;

	double d2 = 0.5 * (10 * pow(a1,2) + a2 - 6 * b1 + 2 * b2) -
		((128/3) * pow(a1,3) - a3/6 + 2 * a1 * b1 - a1 * b2 + 50 * c1 - 11 *
		 c2 + 3 * c3 - c4);
	double d3 = (2 * pow(a1,2) - b1) - (1/3) * (88 * pow(a1,3) + 3 * a1 * 
			(5 * b1 - 2 * b2)) + 3 * (35 * c1 - 6 * c2 + c3);
	double d4 = (-20 * pow(a1,3)/3 + a1 * (-4 * b1 + b2) - 10 * c1 + c2);


	double z1 = d2 - d3 + d4;
	double z2 = d3 - d4;
	double z3 = d4;
	printf("z1 è % .5e\n ", z1);
	printf("z2 è % .5e\n ", z2);
	printf("z3 è % .5e\n ", z3);

	printf("p è % .5e\n ", p(strike));
	printf("p_dx è % .5e\n ", p_dx(strike));
	printf("p_dxx è % .5e\n ", p_dxx(strike));
	double BC = BSBasketOptionPricer::getOptionPrice() + 
		exp(-riskFreeRate) * strike * (z1 * p(strike) + z2 * p_dx(strike) +
				z3 * p_dxx(strike));
	return BC;

}

double JuBasketOptionPricer::p(double x)
{
	return  1/(sqrt(2 * M_PI) * s) * exp(-pow(x - m, 2)/(2 * pow(s,2)));
}


double JuBasketOptionPricer::p_dx(double x)
{
	return -sqrt(2)*s*(-2*m + 2*x)*exp(-pow(s,2)*pow(-m + x,2)/2)/(4*sqrt(M_PI));
}


double JuBasketOptionPricer::p_dxx(double x)
{
	return sqrt(2)*s*(pow(s,2)*pow(m - x,2) - 1)*exp(-pow(s,2)*pow(m - x,2)/2)/(2*sqrt(M_PI));
}
