#include "BasketOptionFormulaPricers.hpp"
#include "bsformula.hpp"
#include "Basket.hpp"
#include "ProcessBiVariateLognormalAbstract.hpp"
#include "ProcessNVariateLognormal.hpp"
#include "LognormalSumDistribution.hpp"
#include "Functional.hpp"
#include "EqSystemSolver.hpp"
#include "LeastSquareSolver.hpp"
#include "NormalDistribution.hpp"
#include "BSPricer.hpp"
#include "Constraints.hpp"
#include <cmath>
#include <algorithm>

BSBasketOptionPricer::BSBasketOptionPricer(const Option *opzione, Process *processo, double riskFreeRate): OptionPricer(opzione, processo, riskFreeRate)
{

	Basket* underlyingBasket = (Basket*)(((BasketOption*) option)->getUnderlying());
	basketMultiplier = underlyingBasket->getMultiplier();
	double sigma1 = ((ProcessBiVariateLognormalAbstract*) processo)->getSigma1();
	double sigma2 = ((ProcessBiVariateLognormalAbstract*) processo)->getSigma2();
	double rho = ((ProcessBiVariateLognormalAbstract*) processo)->getRho();
	double w1 = underlyingBasket->get_w1();
	double w2 = underlyingBasket->get_w2();

	basketSigma = sqrt(pow(w1 * sigma1,2) 
			+ pow(w2 * sigma2,2) 
			+ 2*rho*w1*w2*sigma1*sigma2);
};

BSBasketOptionPricer::BSBasketOptionPricer(const NbasketOption *opzione, Process *processo, double riskFreeRate): OptionPricer(opzione, processo, riskFreeRate)
{
	Nbasket* underlyingBasket =dynamic_cast<Nbasket*>(option->getUnderlying());
	basketMultiplier = underlyingBasket->getMultiplier();
	std::vector<double>* sigma = 
		dynamic_cast<ProcessNVariateLognormal*> (processo)->getSigma();
	std::vector<std::vector<double>> * rho = 
		dynamic_cast<ProcessNVariateLognormal*>(processo)->getRho();
	const std::vector<double> * w = underlyingBasket->get_weights();

	basketSigma = 0;

	for (size_t i = 0; i < w -> size(); ++i)
	{
		for (size_t j = 0; j < w -> size(); ++j)
		{
			basketSigma += (*w)[i] * (*w)[j] * (*sigma)[i] * (*sigma)[j] * (*rho)[i][j];
		}
	}
	basketSigma = sqrt(basketSigma);
}

double BSBasketOptionPricer::getOptionPrice()
{

	double price = bsprice(basketMultiplier,
			option->getStrike() * basketMultiplier,
			riskFreeRate,
			option->getExpiry(),
			basketSigma,
			0,
			1);
	return price;

};

double BSBasketOptionPricer1::getOptionPrice()
{

	Basket* underlyingBasket = (Basket*)(((BasketOption*) option)->getUnderlying());
	double sigma1 = ((ProcessBiVariateLognormalAbstract*) processo)->getSigma1();
	double sigma2 = ((ProcessBiVariateLognormalAbstract*) processo)->getSigma2();
	double rho = ((ProcessBiVariateLognormalAbstract*) processo)->getRho();
	double w1 = underlyingBasket->get_w1();
	double w2 = underlyingBasket->get_w2();

	LognormalSumDistribution phi(riskFreeRate, w1, w2, rho, sigma1, sigma2);
	
	double M2 = phi.M2();
	
	double squareBasketSigma = (2 * log(M2) - riskFreeRate)/3;
	double basketSigma = sqrt(squareBasketSigma);

	double price = bsprice(underlyingBasket->getMultiplier(),
			option->getStrike() * underlyingBasket->getMultiplier(),
			riskFreeRate,
			option->getExpiry(),
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
//	printf("y0 is % .5e\n", LogNormalDistribution::M1(x[0],x[1],x[2]));
//	printf("y1 is % .5e\n", LogNormalDistribution::M2(x[0],x[1],x[2]));
//	printf("y2 is % .5e\n", LogNormalDistribution::M3(x[0],x[1],x[2]));
	return y;
};

std::vector<double> GeneralizedBSBasketOptionPricer::Functional4MomentsCalculation2::
operator()(const std::vector<double> & x) const
{
	double y0 = LogNormalDistribution::M1(x[0], x[1], x[2]) - phiM1;
	double y1 = LogNormalDistribution::M2(x[0], x[1], x[2]) - phiM2;
	double y2 = pow(LogNormalDistribution::M3(x[0], x[1], x[2]) - phiM3,2) +
		pow(LogNormalDistribution::M4(x[0], x[1], x[2]) - phiM4,2)/100;
	std::vector<double> y = {y0, y1, y2};
//	printf("y0 is % .5e\n", LogNormalDistribution::M1(x[0],x[1],x[2]));
//	printf("y1 is % .5e\n", LogNormalDistribution::M2(x[0],x[1],x[2]));
//	printf("y2 is % .5e\n", LogNormalDistribution::M3(x[0],x[1],x[2]));
	return y;
};

std::vector<double> GeneralizedBSBasketOptionPricer::Functional4MomentsCalculation3::
operator()(const std::vector<double> & x) const
{
	double y1 = (LogNormalDistribution::M1(x[0], x[1], x[2]) - phiM1)*100000;
	double y2 = (LogNormalDistribution::M2(x[0], x[1], x[2]) - phiM2)*10000;
	double y3 = (LogNormalDistribution::M3(x[0], x[1], x[2]) - phiM3)*1000;
	double y4 = (LogNormalDistribution::M4(x[0], x[1], x[2]) - phiM4);

	printf("x0 is % .5e\n", x[0]);
	printf("x1 is % .5e\n", x[1]);
	printf("x2 is % .5e\n", x[2]);
	
	printf("y0 is % .5e\n", y1);
	printf("y1 is % .5e\n", y2);
	printf("y2 is % .5e\n", y3);
	printf("y3 is % .5e\n", y4);
	std::vector<double> y = {y1, y2, y3, y4};
	return y;
};

std::vector<double> GeneralizedBSBasketOptionPricer::Functional4MomentsCalculation5thMoment::
operator()(const std::vector<double> & x) const
{
	double y1 = (LogNormalDistribution::M1(x[0], x[1], x[2]) - phiM1)*100000;
	double y2 = (LogNormalDistribution::M2(x[0], x[1], x[2]) - phiM2)*10000;
	double y3 = (LogNormalDistribution::M3(x[0], x[1], x[2]) - phiM3)*1000;
	double y4 = (LogNormalDistribution::M4(x[0], x[1], x[2]) - phiM4);
	double y5 = (LogNormalDistribution::M5(x[0], x[1], x[2]) - phiM5);

//	printf("x0 is % .5e\n", x[0]);
//	printf("x1 is % .5e\n", x[1]);
//	printf("x2 is % .5e\n", x[2]);
//	
//	printf("y0 is % .5e\n", y1);
//	printf("y1 is % .5e\n", y2);
//	printf("y2 is % .5e\n", y3);
//	printf("y3 is % .5e\n", y4);
//	printf("y4 is % .5e\n", y4);
	std::vector<double> y = {y1, y2, y3, y4, y5};
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
	//printf("diagonal : % .5e  %.5e  %.5e\n",dM1_dtau,dM2_dm, dM3_ds);
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
	Basket* underlyingBasket = (Basket*)(((BasketOption*) option)->getUnderlying());
	double sigma1 = ((ProcessBiVariateLognormalAbstract*) processo)->getSigma1();
	double sigma2 = ((ProcessBiVariateLognormalAbstract*) processo)->getSigma2();
	double rho = ((ProcessBiVariateLognormalAbstract*) processo)->getRho();
	double w1 = underlyingBasket->get_w1();
	double w2 = underlyingBasket->get_w2();

	LognormalSumDistribution phi(riskFreeRate, w1, w2, rho, sigma1, sigma2);

	double M1 = phi.M1();
	double M2 = phi.M2();
	double M3 = phi.M3();
	double M4 = phi.M4();
	double M5 = phi.M5();
	printf("the moments of the lognormal sum are : % .5f  %.5f %.5f %.5f %.5f\n", M1, M2, M3, M4, M5);
	double basketSigma = sqrt(pow(w1 * sigma1,2) 
			+ pow(w2 * sigma2,2) 
			+ 2*rho*w1*w2*sigma1*sigma2);

	std::vector<double> x0 = {0, riskFreeRate - 0.5 * pow(basketSigma,2), basketSigma};
	std::vector<int> index = {0}; 
	std::vector<double> upperBound = {-0.01};
        std::vector<double> lowerBound = {0.3};
	Constraints constraints({0}, {-0.01}, {0.3});
//	EqSystemSolver solver(new Functional4MomentsCalculation(M1,M2,M3),
//				//new Jacobian4MomentsCalculation(), 
//				x0, 
//				&constraints);
	
	LeastSquaresSolver solver(new Functional4MomentsCalculation5thMoment(M1,M2,M3,M4,M5),
			//	new Jacobian4MomentsCalculation(), 
				x0);
	solver.solve();

	std::vector<double> x = solver.getSol();

	double strike = option->getStrike();
	double multiplier = underlyingBasket -> getMultiplier();

	double tau = x[0];
	double m = x[1];
	double sigma = x[2];
	//printf("% .5e  %.5e  %.5e\n",tau, m, sigma);

	LogNormalDistribution* psi = new LogNormalDistribution(tau, m, sigma);

	printf("the moments of the approximating lognormal distribution are: %.5f  %.5f  %.5f %.5f %.5f\n",psi->M1(), psi->M2(), psi->M3(), psi->M4(), psi->M5());
	double T = option->getExpiry();
	BSPricer pricer(psi);
	double price = pricer.bsformula(riskFreeRate, T, strike, multiplier);
/*
	double V = sqrt(log((M2 - 2 * tau * M1 + pow(tau,2))/(pow(M1 - tau,2))));

	double d1 = (log(M1 - tau) - log(strike - tau) + 0.5 * pow(V,2)) / V;

	double d2 = d1 - V;


	CumulativeNormalDistribution N(0, 1);

	double price = exp(-riskFreeRate * T) * ((M1 - tau) * N(d1) - (strike - tau) * N(d2));
*/
	printf("% .5e  %.5e  %.5e\n",riskFreeRate, T, strike);
	return price;

}
