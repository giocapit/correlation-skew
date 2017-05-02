#include "BasketOptionFormulaPricers.hpp"
#include "bsformula.hpp"
#include "Basket.hpp"
#include "ProcessBiVariateLognormalAbstract.hpp"
#include <cmath>

double BSBasketOptionPricer::getOptionPrice()
{

	Basket* underlyingBasket = (Basket*)(((BasketOption*) opzione)->getUnderlying());
	double sigma1 = ((ProcessBiVariateLognormalAbstract*) processo)->getSigma1();
	double sigma2 = ((ProcessBiVariateLognormalAbstract*) processo)->getSigma2();
	double rho = ((ProcessBiVariateLognormalAbstract*) processo)->getRho();
	double w1 = underlyingBasket->get_w1();
	double w2 = underlyingBasket->get_w2();
	double basketSigma = sqrt(pow(w1 * sigma1,2) 
				+ pow(w2 * sigma2,2) 
				+ 2*rho*w1*w2*sigma1*sigma2);

	double price = bsprice(underlyingBasket->getMultiplier(),
			opzione->getStrike() * underlyingBasket->getMultiplier(),
			riskFreeRate,
			opzione->getExpiry(),
			basketSigma,
			0,
			1);
	return price;

	

};

double GeneralizedBSBasketOptionPricer::getOptionPrice()
{
	Basket* underlyingBasket = (Basket*)(((BasketOption*) opzione)->getUnderlying());
	double sigma1 = ((ProcessBiVariateLognormalAbstract*) processo)->getSigma1();
	double sigma2 = ((ProcessBiVariateLognormalAbstract*) processo)->getSigma2();
	double rho = ((ProcessBiVariateLognormalAbstract*) processo)->getRho();
	double w1 = underlyingBasket->get_w1();
	double w2 = underlyingBasket->get_w2();
	return 0;

}
