#include "froot.hpp"
#include "bsformula.hpp"
#include "Functional.hpp"

class FunctionalForImpliedVolatilityCalculation: public Functional
{
	private:
		double spot;
		double optPrice;
		double strike;
		double riskFree;
		double T;
	public:
		FunctionalForImpliedVolatilityCalculation(double spot_, double optPrice_, double strike_, double riskFree_, double T_)
		{
			spot = spot_;
			optPrice = optPrice_;
			strike = strike_;
			riskFree = riskFree_;
			T = T_;
		}
		double operator()(double vol) const
		{

			double priceBS = bsprice(spot,
										strike,
										riskFree,
										T,
										vol,
										0.0,
										1);
			return priceBS-optPrice;
		}


};

double bsImplVol(double spot, double optPrice, double strike,double riskFree,double T)
{
	FunctionalForImpliedVolatilityCalculation f = FunctionalForImpliedVolatilityCalculation( spot,  optPrice,  strike, riskFree, T);
	double vol = bisection(&f,0.02,2);//,1e-8);
	return vol;
}
