#include "MCOptionPricer.hpp"
#include "Equity.hpp"
#include "BasketOption.hpp"
#include "MCResults.hpp"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <string>
#include <time.h>

#include "ProcessBiVariateLognormal.hpp"
#include "bsformula.hpp"

using namespace std;

int main (int argc,char* argv[])
{
	if (argc < 1) { // Check the value of argc. If not enough parameters have been passed, inform user and exit.
		std::cout << "Usage is ...\n"; // Inform the user of how to use the program
		std::cin.get();
		exit(0);
	} else { // if we got enough parameters...
		int nSim= 1000000;
		double multiplier = 100;
		double w1 = 0.3;
		double w2 = 0.7;
		double strike = 1;
		double sigma1 = 0.2;
		double sigma2 = 0.3;
		double rho = 0.142;
		double expiry = 1;
		double riskFreeRate = 0.03;
		Option::type cp = Option::put;
		Option::type cpComponents = Option::put;

		std::cout << argv[0];
		for (int i = 1; i < argc; i++) { /* We will iterate over argv[] to get the parameters stored inside.
		 * Note that we're starting on 1 because we don't need to know the
		 * path of the program, which is stored in argv[0] */
			string arg = string(argv[i]);
			if (i + 1 != argc)
			{// Check that we haven't finished parsing already
				if (arg == "-riskFree") {
					riskFreeRate = atof(argv[i + 1]);
				} else if (arg == "-s1") {
					sigma1 = atof(argv[i + 1]);
				} else if (arg == "-s2") {
					sigma2 = atof(argv[i + 1]);
				} else if (arg == "-rho") {
					rho = atof(argv[i + 1]);
				} else if (arg == "-w1") {
					w1 = atof(argv[i + 1]);
				} else if (arg == "-w2") {
					w2 = atof(argv[i + 1]);
				} else if (arg == "-T") {
					expiry = atof(argv[i + 1]);
				} else if (arg == "-Nsim") {
					nSim = atof(argv[i + 1]);
				} else if (arg == "-strike") {
					strike = atof(argv[i + 1]);
				} else {
					std::cout << "Not enough or invalid arguments, please try again.\n";
					exit(0);
				}
			std::cout << argv[i] << " ";
			}
			i = i + 1;
		}


		Equity equity1 = Equity(multiplier);
		Equity equity2 = Equity(multiplier);

		Basket basket = Basket(&equity1, &equity2, w1, w2);
		BasketOption opzione = BasketOption(expiry, &basket,  strike,cp);

		NormalDistributionAntitetica* N1 = new NormalDistributionAntitetica();
		NormalDistributionAntitetica* N2 = new NormalDistributionAntitetica();

		ProcessBiVariateLognormal process = ProcessBiVariateLognormal(sigma1,sigma2,rho, nSim, N1, N2);
		MCOptionPricer pricer = MCOptionPricer(&opzione,
												&process,
												riskFreeRate ,
												nSim,
												new MCResultsErroreMontecarloAntitetico(nSim));
		double priceBasket = pricer.getOptionPrice();

		double priceAsset1 = bsprice(multiplier,
										strike*multiplier,
										riskFreeRate,
										expiry,
										sigma1,
										0,
										cpComponents);

		double priceAsset2 = bsprice(multiplier,
										strike*multiplier,
										riskFreeRate,
										expiry,
										sigma2,
										0,
										cpComponents);

		ofstream miofile;
		miofile.open("C:\\Users\\Giovanni\\Dropbox\\mip\\project_work\\Dati_e_eseguibili\\MCPrice.csv"/*,std::ios_base::app*/);
		miofile << setprecision(11) << -cp*priceBasket + cp * w1 * priceAsset1 + cp * w2 * priceAsset2 << "\n";
		miofile.close();

		return 0;
	}
}
