#include "NormalDistribution.hpp"
#include "BSPricer.hpp"
#include <cmath>

BSPricer::BSPricer(LogNormalDistribution * phi)
{
	this->phi = phi;
}

double BSPricer::bsformula(double r, double T, double strike, double multiplier)
{


	double M_1 = phi->M1();	
	double M_2 = phi->M2();
	double tau = phi->getTau();
	double V = sqrt(log((M_2 - 2 * tau * M_1 + pow(tau,2))/(pow(M_1 - tau,2))));

	double d1 = (log(M_1 - tau) - log(strike - tau) + 0.5 * pow(V,2)) / V;

	double d2 = d1 - V;

	CumulativeNormalDistribution N(0, 1);

	return multiplier * exp(-r * T) * 
				((M_1 - tau) * N(d1) - (strike - tau) * N(d2));

};
