#include "CorrelationExtractors.hpp"
#include "BasketOption.hpp"
#include <cmath>

double SimpleCorrelationExtractor::extract(double sigmaBSComponent1, double sigmaBSComponent2, double optionPrice, double strike, double riskFreeRate, double T)
{
	double w1 = basket->get_w1();
	double w2 = basket->get_w2();
	double multiplier = basket->getMultiplier();
	
	double sigmaBasket = bsImplVol(multiplier, optionPrice, strike * multiplier, riskFreeRate, T);
	double rho = (pow(sigmaBasket,2) - pow(w1,2) * pow(sigmaBSComponent1,2) - pow(w2,2) * pow(sigmaBSComponent2,2)) / 
	(2 * w1 * w2 * sigmaBSComponent1 * sigmaBSComponent2);
	return rho;
}


double MCCorrelationExtractor::extract(double sigmaBSComponent1, double sigmaBSComponent2, double optionPrice, double strike, double riskFreeRate, double T)
{
	BasketOption option = BasketOption(T, basket, strike, BasketOption::call);
	MCOptionPricer pricerBS = MCOptionPricer(&option, procBS, riskFreeRate);
	procBS->setSigma1(sigmaBSComponent1);
	procBS->setSigma2(sigmaBSComponent2);
	FunctionalForCorrelationSkewCalculation f = FunctionalForCorrelationSkewCalculation(procBS, &pricerBS, optionPrice);
	double rho = froot(&f,-1,1);
	return rho;

}

