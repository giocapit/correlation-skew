#include "JuBasketOptionPrice.hpp"
#include "ProcessBiVariateLognormalAbstract.hpp"
#include "ProcessNVariateLognormal.hpp"
#include "bsformula.hpp"
#include <cmath>


JuBasketOptionPricer::JuBasketOptionPricer(const BasketOption *option, Process *process, double riskFreeRate): 
				BSBasketOptionPricer(option, process, riskFreeRate),
				coeffs(0)
{
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

	strike = this->option->getStrike() * multiplier;
	U1 = multiplier;
	double U2_1 = pow(multiplier,2) * (pow(w1,2) * exp(pow(sigma1,2)) + pow(w2,2) * exp(pow(sigma2,2)) + 2 * w1*w2 * exp(sigma1 * sigma2 * rho));
	U2 = pow(multiplier,2) * (pow(w1,2) + pow(w2,2) + 2 * w1*w2);
	m = 2 * log(U1) - 0.5 * log(U2_1);
	s = log(U2_1) - 2 * log(U1);

	coeffs = coeff_for_2basket(multiplier, w1, w2, sigma1, sigma2, rho);

	printf("m è % .5e\n ", m);
	printf("s è % .5e\n ", s);
};

JuBasketOptionPricer::JuBasketOptionPricer(const NbasketOption *option, Process *process, double riskFreeRate): 
				BSBasketOptionPricer(option, process, riskFreeRate),
				coeffs(0)
{
	Nbasket* underlyingBasket = 
		dynamic_cast<Nbasket*>(((NbasketOption*) option)->getUnderlying());
	sigma = 
		(dynamic_cast<ProcessNVariateLognormal*> (processo))->getSigma();
	rhoMatrix = 
		(dynamic_cast<ProcessNVariateLognormal*> (processo))->getRho();
	weights = underlyingBasket->get_weights();
	multiplier = underlyingBasket->getMultiplier();

	strike = this->option->getStrike() * multiplier;
	U1 = 0;
	for (size_t i = 0; i < sigma -> size(); ++i)
	{
			U1 += multiplier * (*weights)[i] * exp(riskFreeRate);
	}
	double U2_1 = 0;
	for (size_t i = 0; i < sigma -> size(); ++i)
	{
		for (size_t j = 0; j < sigma -> size(); ++j)
		{
			U2_1 += pow(multiplier,2) * (*weights)[i] * (*weights)[j] * exp(2 * riskFreeRate + (*sigma)[i] * (*sigma)[j] * (*rhoMatrix)[i][j]);
		}
	}
	U2 = 0;	
	for (size_t i = 0; i < sigma -> size(); ++i)
	{
		for (size_t j = 0; j < sigma -> size(); ++j)
		{
			U2 += pow(multiplier,2) * (*weights)[i] * (*weights)[j];
		}
	}
	
	m = 2 * log(U1) - log(multiplier) - 0.5 * log(U2_1);
	s = log(U2_1) - 2 * log(U1);

	coeffs = coeff_for_Nbasket(multiplier, sigma, rhoMatrix, weights);

	printf("m è % .5e\n ", m);
	printf("s è % .5e\n ", s);
};


double JuBasketOptionPricer::getOptionPrice()
{
	double dU2 = coeffs.dU2;
	double d2U2 = coeffs.d2U2;
	double d3U2 = coeffs.d3U2;
	double a1 = - dU2/(2 * U2);
	double a2 = 2 * a1 * a1 - d2U2/(2*U2);
	double a3 = 6 * a1 * a2 - 4 * pow(a1,3) - d3U2/(2*U2);

	double b1 = coeffs.b1;
	double b2 = pow(a1,2) - 0.5 * a2;

	double c1 = - a1 * b1;
	double k1 = coeffs.k1;
	double k2 = coeffs.k2;
	double c2 = (1/(144 * pow(multiplier,4))) * (9 * k1 + 4 * k2);

	double q1 = coeffs.q1;
	double q2 = coeffs.q2;
	double c3 = (1/(48 * pow(multiplier,3))) * (4 * q1 + q2);
	double c4 = a1 * a2 - 2 * pow(a1,3)/3 - a3/6;

	double d1 = 0.5 * (6 * pow(a1,2) + a2 - 4 * b1 + 2 * b2) - (120 * pow(a1,3) - a3 + 6 * (24 * c1 - 6 * c2 + 2 * c3 - c4))/6;
	double d2 = 0.5 * (10 * pow(a1,2) + a2 - 6 * b1 + 2 * b2) -
		(128 * pow(a1,3)/3 - a3/6 + 2 * a1 * b1 - a1 * b2 + 50 * c1 - 11 *
		 c2 + 3 * c3 - c4);
	double d3 = (2 * pow(a1,2) - b1) - (88 * pow(a1,3) + 3 * a1 * 
			(5 * b1 - 2 * b2) + 3 * (35 * c1 - 6 * c2 + c3))/3;
	double d4 = (-20 * pow(a1,3)/3 + a1 * (-4 * b1 + b2) - 10 * c1 + c2);

//	printf(" è % .5e\n ",  - (120 * pow(a1,3)  )/6 - ( -
//		(128 * pow(a1,3)/3  )) + ( - (88 * pow(a1,3) )/3) - (-20 * pow(a1,3)/3   ));

	double asd = a1*a1*a1;
//	printf(" è % .5e\n ",  - 60 * asd +
//		128 * asd - 88 * asd +20 * asd) ;
	double z1 = d2 - d3 + d4;
	double z2 = d3 - d4;
	double z3 = d4;
/*	printf("b1 è % .5e\n ", b1);
	printf("b2 è % .5e\n ", b2);
	printf("U2 è % .5e\n ", U2);
	printf("dU2 è % .5e\n ", dU2);
	printf("d2U2 è % .5e\n ", d2U2);
	printf("d3U2 è % .5e\n ", d3U2);
	printf("k1 è % .5e\n ", k1);
	printf("k2 è % .5e\n ", k2);
	printf("a1 è % .5e\n ", a1);
	printf("a2 è % .5e\n ", a2);
	printf("d2 è % .5e\n ", d2);
	printf("d3 è % .5e\n ", d3);
	printf("d4 è % .5e\n ", d4);
	printf("q1 è % .5e\n ", q1);
	printf("q2 è % .5e\n ", q2);
	printf("z1 è % .5e\n ", z1);
	printf("z2 è % .5e\n ", z2);
	printf("z3 è % .5e\n ", z3);
	printf("c1 è % .5e\n ", c1);
	printf("d1 - d2 + d3 - d4 è % .5e\n ", d1 - d2 + d3 - d4);
	printf("c1 + a1*b1 è % .10e\n ", c1 + a1 * b1);
*/
	double logstrike = log(strike);
/*	printf("p è % .5e\n ", p(logstrike));
	printf("p_dx è % .5e\n ", p_dx(logstrike));
	printf("p_dxx è % .5e\n ", p_dxx(logstrike));
	printf("p_dxx è % .5e\n ", BSBasketOptionPricer::getOptionPrice());
*/
	double BC = //BSBasketOptionPricer::getOptionPrice() +
	       exp(m + 0.5 * s - riskFreeRate) * bsprice(multiplier, strike, m + 0.5 * s, 1,sqrt( s), 0, 1) +	
		exp(-riskFreeRate) * strike * (z1 * p(logstrike) + z2 * p_dx(logstrike) +
				z3 * p_dxx(logstrike));
	return BC;

}

double JuBasketOptionPricer::p(double x)
{
	return  1/(sqrt(2 * M_PI) * s) * exp(-pow(x - m, 2)/(2 * pow(s,2)));
}


double JuBasketOptionPricer::p_dx(double x)
{
	return -sqrt(2)*(-2*m + 2*x)*exp(-pow(-m + x,2)/(2*pow(s,2)))/(4*sqrt(M_PI)*pow(s,3));
}


double JuBasketOptionPricer::p_dxx(double x)
{
	return sqrt(2)*(-1 + pow(m - x,2)/pow(s,2))*exp(-pow(m - x,2)/(2*pow(s,2)))/(2*sqrt(M_PI)*pow(s,3));
}

JuBasketOptionPricer::coefficients::coefficients(double multiplier)
{
	this -> multiplier = multiplier;
}

JuBasketOptionPricer::coeff_for_2basket::coeff_for_2basket(double multiplier,
						double w1,
						double w2,
						double sigma1,
						double sigma2,
						double rho): coefficients(multiplier)
{

	this -> w1 = w1;
	this -> w2 = w2;
	this -> sigma1 = sigma1;
	this -> sigma2 = sigma2;
	this -> rho = rho;
	
	double rho_11 = pow(sigma1,2);
	double rho_12 = rho * sigma1 * sigma2;
	double rho_22 = pow(sigma2,2);
	
	dU2 = pow(multiplier,2) * (rho_11 * pow(w1,2) + rho_22 * pow(w2,2) + 2*rho_12 * w1*w2);
	d2U2 = pow(multiplier,2) * (pow(rho_11,2) * pow(w1,2) + pow(rho_22,2) * pow(w2,2) + 2*pow(rho_12,2) * w1*w2);

	d3U2 = pow(multiplier,2) * (pow(rho_11,3) * pow(w1,2) + pow(rho_22,3) * pow(w2,2) + 2*pow(rho_12,3) * w1*w2);
	
	b1 = 0.5 * (pow(w1,3) * pow(rho_11,2) + 
			pow(w1,2) * w2 * (2 * rho_12 * rho_11 + pow(rho_12,2)) + 
			w1 * pow(w2,2) * (2 * rho_12 * rho_22 + pow(rho_12,2)) + 
			pow(w2,3) * pow(rho_22,2));
	k1 = 8 * pow(multiplier,4) * (pow(w1,4) * pow(rho_11,3) + 
			2 * pow(w1,3) * w2 * (rho_12 * pow(rho_11,2) + rho_11 * pow(rho_12,2)) + 
			pow(w1,2) * pow(w2,2) * (rho_12 * (pow(rho_11,2) + pow(rho_22,2)) + pow(rho_12,2) * (rho_11 + rho_22) + 2 * pow(rho_12,3)) + 
			2 * w1 * pow(w2,3) * (rho_12 * pow(rho_22,2) + pow(rho_12,2) * rho_22) + 
			pow(w2,4) * pow(rho_22,3)) + 2 * dU2 * d2U2 ;
	k2 = 6 * pow(multiplier,4) * (pow(w1,4) * pow(rho_11,3) + 
			pow(w1,3) * w2 * (3 * rho_12 * pow(rho_11,2) + pow(rho_12,3)) + 
			3 * pow(w1,2) * pow(w2,2) * pow(rho_12,2) * (rho_11 + rho_22) + 
			w1 * pow(w2,3) * (3 * rho_12 * pow(rho_22,2) + pow(rho_12,3)) + 
			pow(w2,4) * pow(rho_22,3));
	q1 = 6 * pow(multiplier,3) * (pow(w1 * rho_11,3) +
			pow(w1,2) * w2 * (rho_12 * pow(rho_11,2) + pow(rho_12,2) * rho_11 + pow(rho_12,3)) +
			w1 * pow(w2,2) * (rho_12 * pow(rho_22,2) + pow(rho_12,2) * rho_22 + pow(rho_12,3)) +
			pow(w2 * rho_22,3));
	q2 = 8 * pow(multiplier,3) * (pow(w1 * rho_11,3) +
			3 * pow(w1,2) * w2 * pow(rho_12,2) * rho_11 +
			3 * w1 * pow(w2,2) * pow(rho_12,2) * rho_22 +
			pow(w2 * rho_22,3));
};

JuBasketOptionPricer::coeff_for_Nbasket::coeff_for_Nbasket(double multiplier,
					std::vector<double> * sigma,
					std::vector<vector<double>> * rhoMatrix,
					const std::vector<double> * weights): coefficients(multiplier)
{
	this->sigma = sigma;
	this->rhoMatrix = rhoMatrix;
	this->weights = weights;

	//dU2:

	for (size_t i = 0; i < sigma -> size(); ++i)
	{
		for (size_t j = 0; j < sigma -> size(); ++j)
		{
			dU2 += pow(multiplier,2) * (*weights)[i] * (*weights)[j] * (*sigma)[i] * (*sigma)[j] * (*rhoMatrix)[i][j];
		}
	}

		
	//d2U2:
	
	for (size_t i = 0; i < sigma -> size(); ++i)
	{
		for (size_t j = 0; j < sigma -> size(); ++j)
		{
			d2U2 += pow(multiplier,2) * (*weights)[i] * (*weights)[j] * pow((*sigma)[i] * (*sigma)[j] * (*rhoMatrix)[i][j],2);
		}
	}
	
	//d3U2:
	
	for (size_t i = 0; i < sigma -> size(); ++i)
	{
		for (size_t j = 0; j < sigma -> size(); ++j)
		{
			d3U2 += pow(multiplier,2) * (*weights)[i] * (*weights)[j] * pow((*sigma)[i] * (*sigma)[j] * (*rhoMatrix)[i][j],3);
		}
	}

	//b1:
	
	for (size_t i = 0; i < sigma -> size(); ++i)
	{
		for (size_t j = 0; j < sigma -> size(); ++j)
		{
			for (size_t k = 0; k < sigma -> size(); ++k)
			{
				b1 += (*weights)[i] * (*weights)[j] * (*weights)[k] 
					* (*sigma)[i] * (*sigma)[k] * (*rhoMatrix)[i][k]
					* (*sigma)[j] * (*sigma)[k] * (*rhoMatrix)[j][k];
			}
		}
	}
	b1 = 0.5 * b1;
	
	
	//k1: 
	
	for (size_t i = 0; i < sigma -> size(); ++i)
	{
		for (size_t j = 0; j < sigma -> size(); ++j)
		{
			for (size_t k = 0; k < sigma -> size(); ++k)
			{
				for (size_t l = 0; l < sigma -> size(); ++l)
				{
					k1 += (*weights)[i] * (*weights)[j] * (*weights)[k] * (*weights)[l]
						* (*sigma)[i] * (*sigma)[l] * (*rhoMatrix)[i][l]
						* (*sigma)[j] * (*sigma)[k] * (*rhoMatrix)[j][k]
						* (*sigma)[l] * (*sigma)[k] * (*rhoMatrix)[l][k];
				}
			}
		}
	}
	k1 = 8 * pow(multiplier,4) * k1 + 2 * dU2 * d2U2;

	
	
	//k2:
	for (size_t i = 0; i < sigma -> size(); ++i)
	{
		for (size_t j = 0; j < sigma -> size(); ++j)
		{
			for (size_t k = 0; k < sigma -> size(); ++k)
			{
				for (size_t l = 0; l < sigma -> size(); ++l)
				{
					k2 += (*weights)[i] * (*weights)[j] * (*weights)[k] * (*weights)[l]
						* (*sigma)[i] * (*sigma)[l] * (*rhoMatrix)[i][l]
						* (*sigma)[j] * (*sigma)[l] * (*rhoMatrix)[j][l]
						* (*sigma)[l] * (*sigma)[k] * (*rhoMatrix)[l][k];
				}
			}
		}
	}
	k2 = 6 * pow(multiplier,4) * k2;
		
	//q1:
	
	for (size_t i = 0; i < sigma -> size(); ++i)
	{
		for (size_t j = 0; j < sigma -> size(); ++j)
		{
			for (size_t k = 0; k < sigma -> size(); ++k)
			{
				q1 += (*weights)[i] * (*weights)[j] * (*weights)[k] 
					* (*sigma)[i] * (*sigma)[k] * (*rhoMatrix)[i][k]
					* pow((*sigma)[j] * (*sigma)[k] * (*rhoMatrix)[j][k],2);
			}
		}
	}
	q1 = 6 * pow(multiplier,3) * q1;
	
	//q2
	
	for (size_t i = 0; i < sigma -> size(); ++i)
	{
		for (size_t j = 0; j < sigma -> size(); ++j)
		{
			for (size_t k = 0; k < sigma -> size(); ++k)
			{
				q2 += (*weights)[i] * (*weights)[j] * (*weights)[k] 
					* (*sigma)[i] * (*sigma)[j] * (*rhoMatrix)[i][j]
					* (*sigma)[i] * (*sigma)[k] * (*rhoMatrix)[i][k]
					* (*sigma)[j] * (*sigma)[k] * (*rhoMatrix)[j][k];
			}
		}
	}
	q2 = 8 * pow(multiplier,3) * q2;
	
	
}
