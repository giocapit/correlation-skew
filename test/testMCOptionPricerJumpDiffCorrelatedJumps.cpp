#include "MCOptionPricer.hpp"
#include "BasketOption.hpp"
#include "Equity.hpp"
#include "Basket.hpp"
#include "ProcessBiVariateJumpDiffusionWithCorrelatedJumps.hpp"
#include <iostream>
#include <cmath>

void testMCOptionPricerBivariateJumpDiffCorrelatedJumps()
{
	int nSim = 300000;
	int dim = 100;				//numero di step di ogni cammino
	double spot1 = 100;
	double spot2 = 100;
	double w1[] = 				{0.7, 	0.7, 	0.7, 	0.7, 	0.7,	0.7,	0.7,	1,		0.7};
	double w2[] = 				{0.3, 	0.3, 	0.3, 	0.3, 	0.3,	0.3,	0.3,	0,		0.3};
	double strike[] = 			{0.70,	0.71,	1.28,	1.29,	1.30,	1,		1,		1.3,		0.7};
	double lambda1[] = 			{0.3, 	0.3, 	0.3, 	0.3, 	0.3,	0.3,	0,		0.3,		0.3}	;
	double J1 = 0.4;
	double sigma1 = 0.2;

	double lambda2[] = 			{0.5, 	0.5, 	0.5, 	0.5, 	0.5,	0.5,	0,		0.5,	0.5};
	double J2 = 0.2;
	double sigma2 = 0.3;
	double rho_diffusion[]= 	{0.5, 	0.5, 	0.5, 	0.5, 	0.5,	0.5,	0.5,	0.5,	0.5};
	double rho_jumps[] = 		{0.5, 	0.5, 	0.5, 	0.5, 	0.5,	0,		0,		0,		0};
	double expiry = 1;
	double riskFreeRate = 0.03;
	Option::type cp;
	cp = Option::call;
	double y[] = 				{0,		0,		0,		0,		0,		16.2391,9.44918, 5.11705, 35.9799};


	int numTests = sizeof(strike)/sizeof(double);
	double maxError = 0.0;

	for (int i = 0;i<numTests;i++)
	{
		Equity equity1 = Equity(spot1);
		Equity equity2 = Equity(spot2);

		Basket basket = Basket(&equity1, &equity2, w1[i], w2[i]);
		//NormalDistributionAntitetica N1 = NormalDistributionAntitetica(dim);
		//NormalDistributionAntitetica N2 = NormalDistributionAntitetica(dim);
		//BiVariateJumpDistributionAntitetica X = BiVariateJumpDistributionAntitetica(lambda1[i],lambda2[i],rho_jumps[i]);


		ProcessBiVariateJumpDiffusionWithCorrelatedJumps process = ProcessBiVariateJumpDiffusionWithCorrelatedJumps(lambda1[i],
				J1,
				sigma1,
				lambda2[i],
				J2,
				sigma2,
				rho_diffusion[i],
				rho_jumps[i],
				//&N1,
				//&N2,
				//&X,
				nSim,
				dim);
		BasketOption opzione = BasketOption(expiry, &basket,  strike[i],cp);

		MCOptionPricer pricer = MCOptionPricer(&opzione, &process, riskFreeRate , nSim);
		//	double price = pricer.getOptionPriceWithGsl();
		double price = pricer.getOptionPrice();
		double error = fabs(price - y[i]);
		double MCerror = pricer.getErroreMontecarlo();
		if (error > maxError)
			maxError = error;

		if (i == 5)
		{
			std::cout << "price: " << price << "	";
			std::cout << "y: " << y[i] << "   caso 6 rho_jump = 0, il prezzo deve essere simile a quello ottenuto con il processo bivariato a salti semplice\n";
			std::cout << "Montecarlo error: " << MCerror << "\n";
		}else if (i == 6){
			std::cout << "price: " << price << "	";
			std::cout << "y: " << y[i] << "   caso 7: rho_jump = 0, lambda =0, il prezzo deve essere simile a quello ottenuto con il processo bivariato lognormale\n";
			std::cout << "Montecarlo error: " << MCerror << "\n";
		}else if (i == 8){
			std::cout << "price: " << price << "	";
			std::cout << "y: " << y[i] << "   caso 9: rho_jump = 0, il prezzo deve essere simile a quello ottenuto con il processo bivariato a salti semplice\n";
			std::cout << "Montecarlo error: " << MCerror << "\n";
		}else{
			std::cout << "price: " << price << "	";
			std::cout << "y: " << y[i] << "\n";
			std::cout << "Montecarlo error: " << MCerror << "\n";
		}
	}
	std::cout << "Maximum error: " << maxError << "\n";
}
int main()
{
	testMCOptionPricerBivariateJumpDiffCorrelatedJumps();
}

