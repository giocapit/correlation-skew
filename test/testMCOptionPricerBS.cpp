#include "MCOptionPricer.hpp"
#include "BasketOption.hpp"
#include "Equity.hpp"
#include "Basket.hpp"
#include <iostream>
#include <cmath>

#include "../main/ProcessBiVariateLognormal.hpp"

void testMCOptionPricerBivariateBS()
{
	int nSim= 1000000;
	double spot1[] = {150,150,100};
	double spot2[] = {200,150,100};
	double w1[] = {0.3,0.5,0.7};
	double w2[] = {0.7,0.5,0.3};
	double strike[] = {1.3,1.3,1.3};
	double sigma1[] = {0.5517,0.3,0.2};
	double sigma2[] = {0.9619,0.3,0.3};
	double rho[] = {0.142,1,0.5};
	double expiry = 1;
	double riskFreeRate = 0.03;
	Option::type cp;
        cp = Option::call;
	double y[] = {38.0033, 6.31151,  9.44918};

	int numTests = sizeof(spot1)/sizeof(double);
	double maxError = 0.0;

	for (int i = 0;i<numTests;i++)
	{

	Equity equity1 = Equity(spot1[i]);	
	Equity equity2 = Equity(spot2[i]);

	Basket basket = Basket(&equity1, &equity2, w1[i], w2[i]);
	BasketOption opzione = BasketOption(expiry, &basket,  strike[i],cp);
 
	ProcessBiVariateLognormal process = ProcessBiVariateLognormal(sigma1[i],sigma2[i],rho[i], nSim);
	MCOptionPricer pricer = MCOptionPricer(&opzione, &process, riskFreeRate , nSim);
	double price = pricer.getOptionPrice();
	double MCerror = pricer.getErroreMontecarlo();
	double error = fabs(price - y[i]);
		    if (error > maxError)
			    maxError = error;

	std::cout << "price: " << price << "	"<<"Montecarlo error: " << MCerror << "\n";
	}
	std::cout << "Maximum error: " << maxError << "\n";
}
int main()
{
	testMCOptionPricerBivariateBS();
}









		
