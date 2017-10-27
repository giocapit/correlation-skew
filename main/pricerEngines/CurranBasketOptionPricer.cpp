#include "CurranBasketOptionPricer.hpp"
#include "ProcessBiVariateLognormalAbstract.hpp"
#include "bsformula.hpp"
#include "RectanglesIntegral.hpp"
#include "LognormalDistribution.hpp"
#include <cmath>
#include <functional>

double CurranBasketOptionPricer::getOptionPrice()
{

	Basket* underlyingBasket = (Basket*)(((BasketOption*) option)->getUnderlying());
	double sigma1 = ((ProcessBiVariateLognormalAbstract*) processo)->getSigma1();
	double sigma2 = ((ProcessBiVariateLognormalAbstract*) processo)->getSigma2();
	double rho = ((ProcessBiVariateLognormalAbstract*) processo)->getRho();
	double w1 = underlyingBasket->get_w1();
	double w2 = underlyingBasket->get_w2();
	double basketSigma = sqrt(pow(w1 * sigma1,2) 
			+ pow(w2 * sigma2,2) 
			+ 2*rho*w1*w2*sigma1*sigma2);

	double cov_X1_X = sigma1 * (w1 * sigma1 + w2 * sigma2 * rho);
	double cov_X2_X = sigma2 * (w2 * sigma2 + w1 * sigma1 * rho);

	double a1 = w1;
	double b1 = w2;

	double mu_1 = riskFreeRate - 0.5 * pow(sigma1,2);
	double mu_2 = riskFreeRate - 0.5 * pow(sigma2,2);

	//mean of the arithmetic mean
	double mu = (w1 * mu_1 + w2 * mu_2) / (w1 + w2);

	double multiplier = underlyingBasket->getMultiplier();
	CumulativeNormalDistribution phi;
	double a2 = phi((mu_1 - log(strike))/basketSigma + cov_X1_X/basketSigma);
	double b2 = phi((mu_2 - log(strike))/basketSigma + cov_X2_X/basketSigma);

	double I1 = a1*a2 + b1*b2;
	double I2 = strike * phi((mu - log(strike))/basketSigma);

	double C_11 = pow(sigma1*sigma2*w2,2)*(-pow(rho,2) + 1)/(2*rho*sigma1*sigma2*w1*w2 + pow(sigma1*w1,2) + pow(sigma2*w2,2));
	double C_12 = pow(sigma1*sigma2,2)*w1*w2*(pow(rho,2) - 1)/(2*rho*sigma1*sigma2*w1*w2 + pow(sigma1*w1,2) + pow(sigma2*w2,2));
	double C_22 = pow(sigma1*sigma2*w1,2)*(-pow(rho,2) + 1)/(2*rho*sigma1*sigma2*w1*w2 + pow(sigma1*w1,2) + pow(sigma2*w2,2));

	//means conditioned to geometric mean = strike
	double mucond1 = mu_1 + (cov_X1_X/pow(basketSigma,2)) * (log(strike) - mu); 
	double mucond2 = mu_2 + (cov_X2_X/pow(basketSigma,2)) * (log(strike) - mu); 
	
	//conditional mean of the arithmetic mean
	mu_aritm_mean = (1/(w1 + w2)) * 
			(w1 * exp(mucond1 + 0.5 * C_11) +
			 w2 * exp(mucond2 + 0.5 * C_22));
	//Conditional variance of the aritmetic mean
	sigma_aritm_mean = pow(1/(w1 + w2),2) *
			(pow(w1,2) * (exp(2 * mucond1 + 2 * C_11) - exp(2 * mucond1 + C_11))+
			 pow(w2,2) * (exp(2 * mucond2 + 2 * C_22) - exp(2 * mucond2 + C_22))+
			 w1 * w2 * (exp(mucond1 + mucond2 + 0.5 * (C_11 + C_22 + 2 * C_12)) - exp(mucond1 + mucond2 + 0.5 * (C_11 + C_22))));

	printf("C11 % .5e\n", C_11);
	printf("C22 % .5e\n", C_22);
	printf("mu_aritm_mean is % .5e\n", mu_aritm_mean);
	printf("sigma_aritm_mean is % .5e\n", sigma_aritm_mean);
	using std::placeholders::_1;
	std::function<double( double)> bsIntegrand = std::bind(& CurranBasketOptionPricer::integrand, this,  _1, multiplier); 
	
	psi = LogNormalDistribution(0, mu, basketSigma);
	double C2 = exp(-riskFreeRate) * RectanglesIntegral(1000).integrate(bsIntegrand, 0, strike * multiplier);	
	double C1 = I1 - exp(-riskFreeRate) * I2;
	printf("C1 is % .5e\n", C1);
	printf("C2 is % .5e\n", C2);
	return multiplier * (C1) + C2;

};

double CurranBasketOptionPricer::integrand( double x, double multiplier ) const
{
	double mu_eps = (mu_aritm_mean - strike) * multiplier;
	double gamma = sqrt(log(sigma_aritm_mean/pow(mu_eps,2) + 1));
	double beta = log(mu_eps) - 0.5 * pow(gamma,2);
	
	return exp(beta + 0.5 * pow(gamma,2)) * bsprice(multiplier ,multiplier * x, beta + 0.5 * pow(gamma,2), 1, gamma, 0, 1) *
								psi.pdf(strike * multiplier - x);
};


//Matrix([
//[sigma1**2*sigma2**2*w2**2*(-rho**2 + 1)/(2*rho*sigma1*sigma2*w1*w2 + sigma1**2*w1**2 + sigma2**2*w2**2),  sigma1**2*sigma2**2*w1*w2*(rho**2 - 1)/(2*rho*sigma1*sigma2*w1*w2 + sigma1**2*w1**2 + sigma2**2*w2**2)],
//[ sigma1**2*sigma2**2*w1*w2*(rho**2 - 1)/(2*rho*sigma1*sigma2*w1*w2 + sigma1**2*w1**2 + sigma2**2*w2**2), sigma1**2*sigma2**2*w1**2*(-rho**2 + 1)/(2*rho*sigma1*sigma2*w1*w2 + sigma1**2*w1**2 + sigma2**2*w2**2)]])
