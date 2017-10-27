#ifndef curran_basket_option_formula_price_hpp
#define curran_basket_option_formula_price_hpp
#include "OptionPricer.hpp"
#include "BasketOption.hpp"
#include "Functional.hpp"
#include "LognormalDistribution.hpp"

class CurranBasketOptionPricer: public OptionPricer
{
	public:
		CurranBasketOptionPricer(const BasketOption *option, Process *process, double riskFreeRate): OptionPricer(option, process, riskFreeRate)
	{
		strike = this->option->getStrike();
	}

		~CurranBasketOptionPricer(){};

		double getOptionPrice();

	private:
		double integrand(double x, double multiplier) const;

		double sigma_aritm_mean;

		double mu_aritm_mean;

		double strike;

		LogNormalDistribution psi;
		
};
#endif
