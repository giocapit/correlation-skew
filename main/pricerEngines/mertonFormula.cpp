#include "mertonFormula.hpp"
#include <cmath>
#include "bsformula.hpp"

double mertonPrice(double S0,
		double K,
		double r,
		double T,
		double lambda,
		double J,
		double sigma,
		int cp)
{
	double k = J-1;
	double lambdaCap = lambda * (k + 1);
	double rN = r - lambda * k;
	double PV_Merton = exp(-lambdaCap * T) * bsprice(S0, K, rN, T, sigma, 0, cp);
	int factorial = 1;
	double mertAddend;

	for (int i = 1; i <= 30; i++)
	{
		rN = r - lambda * k + i * (log(1+k)/T);
		factorial = factorial * i;
		mertAddend = 1/factorial * 
			exp(-lambdaCap * T) * 
			pow(lambdaCap * T,i) * 
			bsprice(S0, K, rN, T, sigma, 0, cp);
		PV_Merton = PV_Merton + mertAddend;
	}
	return PV_Merton;
}







