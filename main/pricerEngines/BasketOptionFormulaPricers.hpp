#include "OptionPricer.hpp"

class BSBasketOptionPricer: public OptionPricer
{
	public:
		BSBasketOptionPricer(const BasketOption *opzione_, Process *processo_, double riskFreeRate_): OptionPricer(const Option*, Process *, double){};

		~BSBasketOptionPricer();
};

class GeneralizedBSBasketOptionPricer: public OptionPricer{};



