#include "BasketOptionFormulaPricers.hpp"
#include "bsformula.hpp"
#include "Basket.hpp"
#include "BasketOption.hpp"

BSBasketOptionPricer::getOptionPrice()
{

	Basket* underlyingBasket = ((BasketOption*) option)->getUnderlying();
	double sigma1 = (ProcessBiVariateLognormalAbstract*) process->getSigma1();
	double sigma2 = (ProcessBiVariateLognormalAbstract*) process->getSigma2();
	double rho = (ProcessBiVariateLognormalAbstract*) process->getRho();

	double price = bsprice(underlyingPrice->getMultiplier(),
			option->getStrike(),
			riskFreeRate,
			option->getExpiry(),
			basketSigma,
			0,
			1)
	return price;

	

}
