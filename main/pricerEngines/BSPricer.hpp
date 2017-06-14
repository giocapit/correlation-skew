#include "LognormalDistribution.hpp"
#include "OptionPricerClosedFormula.hpp"

class BSPricer : public OptionPricerClosedFormula
{

	private:
		LogNormalDistribution * phi;
	public:
		BSPricer(LogNormalDistribution * phi);
		double bsformula(double r, double T, double strike, double multiplier = 1);
		double getOptionPrice(){return 0.0;};

};	
