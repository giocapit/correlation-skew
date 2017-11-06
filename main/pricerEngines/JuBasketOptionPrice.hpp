#ifndef ju_basket_option_formula_price_hpp
#define ju_basket_option_formula_price_hpp
#include "OptionPricer.hpp"
#include "BasketOption.hpp"
#include "NbasketOption.hpp"
#include "Functional.hpp"
#include "LognormalDistribution.hpp"
#include "BasketOptionFormulaPricers.hpp"

class JuBasketOptionPricer: public BSBasketOptionPricer
{
	public:
		JuBasketOptionPricer(const BasketOption *option, Process *process, double riskFreeRate);

		JuBasketOptionPricer(const NbasketOption *option, Process *process, double riskFreeRate);
		
		~JuBasketOptionPricer(){};

		double getOptionPrice();

	private:
		double strike;

		double p(double x);
		double p_dx(double x);
		double p_dxx(double x);
		double sigma1;
		double sigma2;
		double rho;
		double w1;
		double w2;
		double multiplier;
		double m;
		double s;
		double U1;
		double U2;
};    
#endif
