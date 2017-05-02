#include "OptionPricer.hpp"
#include "BasketOption.hpp"

class BSBasketOptionPricer: public OptionPricer
{
	public:
		BSBasketOptionPricer(const BasketOption *opzione, Process *processo, double riskFreeRate): OptionPricer(opzione, processo, riskFreeRate){};

		~BSBasketOptionPricer(){};

		double getOptionPrice();
};

class GeneralizedBSBasketOptionPricer: public OptionPricer
{
	public:
		GeneralizedBSBasketOptionPricer(const BasketOption *opzione, Process *processo, double riskFreeRate): OptionPricer(opzione, processo, riskFreeRate){};

		~GeneralizedBSBasketOptionPricer(){};

		double getOptionPrice();
};


