#ifndef OptionPricer_hpp 
#define OptionPricer_hpp
#include "Option.hpp"
#include "Process.hpp"

class OptionPricer
{
	protected:
		double riskFreeRate;
		const Option *option;
		Process *processo;
	public:
		OptionPricer();
		OptionPricer(const Option *option_, Process *processo_, double riskFreeRate_)
		{
			option = option_;
			processo = processo_;
			riskFreeRate = riskFreeRate_;
		};
		~OptionPricer();

		double getRiskFreeRate();

		virtual double getOptionPrice()=0;
};
#endif
