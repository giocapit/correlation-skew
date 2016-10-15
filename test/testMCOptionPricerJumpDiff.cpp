#include "MCOptionPricer.hpp"
#include "BasketOption.hpp"
#include "Equity.hpp"
#include "Basket.hpp"
#include "ProcessBiVariateJumpDiffusion.hpp"
#include <iostream>
#include <cmath>

void testMCOptionPricerBivariateJumpDiff()
{
	int nSim = 1000000;
	double spot1 = 100;
	double spot2 = 100;
	double w1[] = 					{0.7,		0.7,		0.7,		0.7,		1,			0.7};
	double w2[] = 					{0.3,		0.3,		0.3,		0.3,		0,			0.3};
	double strike[] = 				{0.70,		0.71,		1.28,		1.30,		1.30,		0.7};
	double lambda1 = 0.3;
	double J1 = 0.4;
	double sigma1 = 0.2;

	double lambda2 = 0.5;
	double J2 = 0.2;
	double sigma2 = 0.3;
	double rho = 0.5;
	double expiry = 1;
	double riskFreeRate = 0.03;
	Option::type cp;
        cp = Option::call;
	double y[] = 					{75.5668,	74.4210,	23.0321,	5.36214,	5.11705,	0};

	Equity equity1 = Equity(spot1);	
	Equity equity2 = Equity(spot2);

 
	int numTests = sizeof(strike)/sizeof(double);
	double maxError = 0.0;

	for (int i = 0;i<numTests;i++)
	{
		Basket basket = Basket(&equity1, &equity2, w1[i], w2[i]);

		ProcessBiVariateJumpDiffusion process = ProcessBiVariateJumpDiffusion(lambda1, J1,sigma1,lambda2, J2, sigma2,rho, nSim);
		BasketOption opzione = BasketOption(expiry, &basket,  strike[i],cp);

		MCOptionPricer pricer = MCOptionPricer(&opzione, &process, riskFreeRate , nSim);
		double price = pricer.getOptionPrice();
		double error = fabs(price - y[i]);
		double MCerror = pricer.getErroreMontecarlo();

		    if (error > maxError)
			    maxError = error;

		    if (i==4)
		    {
		    	std::cout << "price: " << price << "	";
		    	std::cout << "y: " << y[i] << "  caso 5: w2 = 0, il prezzodeve coincidere con il risultato della formula di merton\n";
		    	std::cout << "errore montecarlo: " << MCerror << "	";
		    }else{
		    	std::cout << "price: " << price << "	";
		    	std::cout << "y: " << y[i] << "\n";
		    	std::cout << "errore montecarlo: " << MCerror << "	";
		    }
	}
	std::cout << "Maximum error: " << maxError << "\n";
	std::cout << "Numero di simulazioni: " << nSim << "\n";
}
int main()
{
	testMCOptionPricerBivariateJumpDiff();
}

