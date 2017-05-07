#include "BasketOptionFormulaPricers.hpp"
#include "bsformula.hpp"
#include "Basket.hpp"
#include "ProcessBiVariateLognormalAbstract.hpp"
#include "LognormalSumDistribution.hpp"
#include "Functional.hpp"
#include "EqSystemSolver.cpp"
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

std::vector<double> GeneralizedBSBasketOptionPricer::Functional4MomentsCalculation::
		operator()(const std::vector<double> & x) const
{
	double y0 = LogNormalDistribution::M1(x[0], x[1], x[2]) - phiM1;
	double y1 = LogNormalDistribution::M2(x[0], x[1], x[2]) - phiM2;
	double y2 = LogNormalDistribution::M3(x[0], x[1], x[2]) - phiM3;
	std::vector<double> y = {y0, y1, y2};
	return y;


};

double GeneralizedBSBasketOptionPricer::getOptionPrice()
{
	Basket* underlyingBasket = (Basket*)(((BasketOption*) opzione)->getUnderlying());
	double sigma1 = ((ProcessBiVariateLognormalAbstract*) processo)->getSigma1();
	double sigma2 = ((ProcessBiVariateLognormalAbstract*) processo)->getSigma2();
	double rho = ((ProcessBiVariateLognormalAbstract*) processo)->getRho();
	double w1 = underlyingBasket->get_w1();
	double w2 = underlyingBasket->get_w2();
	
	LognormalSumDistribution phi(riskFreeRate, w1, w2, rho, sigma1, sigma2);

	double M1 = phi.M1();
	double M2 = phi.M2();
	double M3 = phi.M3();

	EqSystemSolver solver(new MultiFunctional(M1,M2,M3),std::vector<double>(3,0));


	return 0;

}
