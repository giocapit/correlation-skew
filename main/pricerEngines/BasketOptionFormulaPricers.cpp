#include "BasketOptionFormulaPricers.hpp"
#include "bsformula.hpp"
#include "Basket.hpp"
#include "ProcessBiVariateLognormalAbstract.hpp"
#include "LognormalSumDistribution.hpp"
#include "Functional.hpp"
#include "EqSystemSolver.hpp"
#include "NormalDistribution.hpp"
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

std::vector<double> GeneralizedBSBasketOptionPricer::Jacobian4MomentsCalculation::
operator()(const std::vector<double> & x) const
{
	double tau = x[0]; double m = x[1]; double s = x[2];

	double dM1_dtau = 1;
	double dM2_dtau = 2 * tau + 2 * exp(m + 0.5 * pow(s,2));
	double dM3_dtau = 3 * pow(tau,2) + 6 * tau * exp(m + 0.5 * pow(s,2)) +
		3 * exp(2 * m + 2 * pow(s,2));
	double dM1_dm = exp(m + 0.5 * pow(s,2));
	double dM2_dm = 2 * tau * exp(m + 0.5 * pow(s,2)) + 
		2 * exp(2 * m + 2 * pow(s,2));
	double dM3_dm = 3 * pow(tau,2) * exp(m + 0.5 * pow(s,2)) + 
		6 * tau * exp(2 *m + 2 * pow(s,2)) + 
		3 * exp(3 * m + 4.5 * pow(s,2));

	double dM1_ds = s * exp(m + 0.5 * pow(s,2));
	double dM2_ds = 2 * tau * s * exp(m + 0.5 * pow(s,2)) + 
		4 * s * exp(2 * m + 2 * pow(s,2));
	double dM3_ds = 3 * pow(tau,2) * s * exp(m + 0.5 * pow(s,2)) + 
		12 * tau * s * exp(2 * m + 2 * pow(s,2)) + 
		9 * s * exp(3 * m + 4.5 * pow(s,2));

	std::vector<double> y = {dM1_dtau,
		dM2_dtau,
		dM3_dtau,
		dM1_dm,
		dM2_dm,
		dM3_dm,
		dM1_ds,	
		dM2_ds,
		dM3_ds};
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

	double basketSigma = sqrt(pow(w1 * sigma1,2) 
			+ pow(w2 * sigma2,2) 
			+ 2*rho*w1*w2*sigma1*sigma2);

	std::vector<double> x0 = {0, riskFreeRate - 0.5 * pow(basketSigma,2), basketSigma};

	EqSystemSolver solver(new Functional4MomentsCalculation(M1,M2,M3),
				new Jacobian4MomentsCalculation(), 
				x0);
	
	solver.solve();

	std::vector<double> y = solver.getSol();

	double strike = opzione->getStrike();

	double tau = y[0];

	double V = sqrt(log((M2 - 2 * tau * M1 + pow(tau,2))/(pow(M1 - tau,2))));

	double d1 = (log(M1 - tau) - log(strike - tau) + 0.5 * pow(V,2)) / V;

	double d2 = d1 - V;

	double T = opzione->getExpiry();

	CumulativeNormalDistribution N(0, 1);

	double price = exp(-riskFreeRate * T) * ((M1 - tau) * N(d1) - (strike - tau) * N(d2));

	return price;

}
