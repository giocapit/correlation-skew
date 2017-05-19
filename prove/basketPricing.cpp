#include "BasketOptionFormulaPricers.hpp"
#include "MCOptionPricer.hpp"
#include "Equity.hpp"
#include "BasketOption.hpp"
#include "ProcessBiVariateLognormal.hpp"
#include "LognormalSumDistribution.hpp"
#include <iostream>

using namespace std;

int main()
{

	int nSim= 1000000;
	double multiplier = 100;
	double w1 = 0.5;
	double w2 = 0.5;
	double strike = 1;
	double sigma1 = 0.3;
	double sigma2 = 0.15;
	double rho = 0.5;
	double expiry = 1;
	double riskFreeRate = 0.02;
	Option::type cp = Option::call;


	Equity equity1 = Equity(multiplier);
	Equity equity2 = Equity(multiplier);

	Basket basket = Basket(&equity1, &equity2, w1, w2);
	BasketOption opzione = BasketOption(expiry, &basket,  strike,cp);

	NormalDistributionAntitetica* N1 = new NormalDistributionAntitetica();
	NormalDistributionAntitetica* N2 = new NormalDistributionAntitetica();

	ProcessBiVariateLognormal process = ProcessBiVariateLognormal(sigma1,sigma2,rho, nSim, N1, N2);
	cout << process.getSigma1();
	cout << process.getSigma2();
	MCOptionPricer montecarlopricer = MCOptionPricer(&opzione,
			&process,
			riskFreeRate ,
			nSim);
	BSBasketOptionPricer bsoptionpricer = BSBasketOptionPricer(& opzione, &process, riskFreeRate); 
	GeneralizedBSBasketOptionPricer genbsoptionpricer = GeneralizedBSBasketOptionPricer(& opzione, &process, riskFreeRate);
	double mcprice = montecarlopricer.getOptionPrice();
	double bsprice = bsoptionpricer.getOptionPrice();
	double genbsprice = genbsoptionpricer.getOptionPrice();
	
	
	LognormalSumDistribution phi(riskFreeRate, w1, w2, rho, sigma1, sigma2);

	double M1 = phi.M1();
	double M2 = phi.M2();
	double M3 = phi.M3();
	
	cout << M1 << "	" << M2 << "	" << M3 << "\n";

	cout << mcprice << endl
		<< bsprice << endl
		<< genbsprice << endl;

	return 0;

}

