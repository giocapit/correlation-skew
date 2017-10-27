#include "JuBasketOptionPrice.hpp"
#include <cmath>


JuBasketOptionPricer(const BasketOption *option, Process *process, double riskFreeRate)::JuBasketOptionPricer
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
	U2 = pow(multiplier,2) * (pow(w1,2) + pow(w2,2) + w1*w2);

	m = 2 * log(U1) - 0.5 * log(U2);
	s = log(U2) - 2 * log(U1);

}

double JuBasketOptionPricer::getOptionPrice()
{

	double dU2 = pow(multiplier,2) * (pow(w1,2) + pow(w2,2) + rho * w1*w2);
	double d2U2 = pow(multiplier,2) * (pow(w1,2) + pow(w2,2) + pow(rho,2) * w1*w2);
	double d3U2 = pow(multiplier,2) * (pow(w1,2) + pow(w2,2) + pow(rho,3) * w1*w2);
	double a1 = - dU2/(2 * U2);
	double a2 = 2 * a1 - d2U2/(2*U2);
	double a3 = 6 * a1 * a2 - 4 * pow(a1,3) - d3U2/(2*U2);

	double b1 = 2 * (pow(w1,3) + pow(w1,2) * w2);



}

double JuBasketOptionPricer::p(double x)
{
	return  1/(sqrt(2 * M_PI) * s) * exp(-pow(x - m, 2)/2 * pow(s,2));
}


double JuBasketOptionPricer::p_dx(double x)
{
	return -sqrt(2)*s*(-2*m + 2*x)*exp(-pow(s,2)*pow(-m + x,2)/2)/(4*sqrt(M_PI));
}


double JuBasketOptionPricer::p_dxx(double x)
{
	return sqrt(2)*s*(pow(s,2)*pow(m - x,2) - 1)*exp(-pow(s,2)*pow(m - x,2)/2)/(2*sqrt(M_PI));
}
