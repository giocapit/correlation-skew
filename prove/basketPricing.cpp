#include "BasketOptionFormulaPricers.hpp"
#include "MCOptionPricer.hpp"
#include "Equity.hpp"
#include "BasketOption.hpp"
#include "ProcessBiVariateLognormal.hpp"
#include <iostream>

using namespace std;

int main()
{

	int nSim= 1000000;
	double multiplier = 100;
	double w1 = 0.5;
	double w2 = 0.5;
	double strike = 1;
	double sigma1 = 0.2;
	double sigma2 = 0.3;
	double rho = 1;//0.142
	double expiry = 1;
	double riskFreeRate = 0.03;
	Option::type cp = Option::call;


	Equity equity1 = Equity(multiplier);
	Equity equity2 = Equity(multiplier);

	Basket basket = Basket(&equity1, &equity2, w1, w2);
	BasketOption opzione = BasketOption(expiry, &basket,  strike,cp);

	NormalDistributionAntitetica* N1 = new NormalDistributionAntitetica();
	NormalDistributionAntitetica* N2 = new NormalDistributionAntitetica();

	ProcessBiVariateLognormal process = ProcessBiVariateLognormal(sigma1,sigma2,rho, nSim, N1, N2);
	MCOptionPricer montecarlopricer = MCOptionPricer(&opzione,
			&process,
			riskFreeRate ,
			nSim);
	BSBasketOptionPricer bsoptionpricer = BSBasketOptionPricer(& opzione, &process, riskFreeRate); 
	double mcprice = montecarlopricer.getOptionPrice();
	double bsprice = bsoptionpricer.getOptionPrice();

	cout << mcprice << endl
		<< bsprice << endl;

	return 0;

}

