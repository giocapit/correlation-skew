#include <stdio.h>

#include "ProcessBiVariateLognormal.hpp"
#include "calculateCorrelationSkew.hpp"
#include "Equity.hpp"
#include "Basket.hpp"
#include "BasketOption.hpp"
#include "MCOptionPricer.hpp"
#include "bsformula.hpp"

extern "C" {

int FooBarRet (int* MyValue,double* output)
{
	double x =100.0;
	double y = static_cast<double>(*MyValue);
	x = x + y;
	*output = x;
  return 0 ;
}

double sum (double* a)
{
	return a[0]+a[1];
}

double Interface_BSprice (
		double vba_spot,
		double vba_riskFree,
		double vba_sigma ,
		double vba_strike ,
		double vba_expiry
)
{
	// Dichiarazioni variabili
	//
	double riskFreeRate;
	double sigma ;
	double strike;
	double spot;
	double expiry;
	// Output
	//

	riskFreeRate = vba_riskFree;
	sigma = vba_sigma ;
	strike = vba_strike;
	spot = vba_spot;
	expiry = vba_expiry;

	double price = bsprice(spot,
			 strike,
			 riskFreeRate,
			 expiry,
			 sigma,
			0,
			1);

	return price;
}
}
