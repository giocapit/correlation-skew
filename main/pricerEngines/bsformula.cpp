#include <cmath>
#include "bsformula.hpp"
#include "NormalDistribution.hpp"

double bsprice(double S0,
		double K,
		double r,
		double T,
		double sigma,
		double q,
		int cp)
{
	double d1, d2;
	d1 = blackD1(S0, K, r, T, sigma, q);
	d2 = blackD2(S0, K, r, T, sigma, q);

	CumulativeNormalDistribution phi;

	return cp*S0*exp(-q*T) * phi(cp * d1) - cp*K*exp(-r*T) * phi(cp * d2);
}

double blackD1(double S0,
		double K,
		double r,
		double T,
		double sigma,
		double q)
{
	double logReturns;
	if (S0 > 0)
		logReturns = log(S0/K);
	else logReturns = 0;
	
	double d1;
	d1 = (logReturns + (r - q + sigma * sigma * 0.5) * T)/(sigma * sqrt(T));
	return d1;
}


double blackD2(double S0,
		double K,
		double r,
		double T,
		double sigma,
		double q)
{
	double d2;
	d2 = blackD1(S0, K, r, T, sigma, q) - sigma*sqrt(T);
	return d2;
}


double delta(double S0,
		double K,
		double r,
		double T,
		double sigma,
		double q,
		int cp)
{
	double d1;
    	d1 = blackD1(S0, K, r, T, sigma, q);

	CumulativeNormalDistribution phi;
	double delta;

    	if (cp == 1)
        	delta = phi(d1) * exp(-q*T);
    	else
        delta = (phi(d1)-1)* exp(-q*T);
	return delta;
}

double vega(double S0,
		double K,
		double r,
		double T,
		double sigma,
		double q)
{
	double d1 = blackD1(S0, K, r, T, sigma, q);
	CumulativeNormalDistribution phi;
	double vega = S0 * sqrt(T) * phi(d1) * exp(-q*T);
	return vega;
}
