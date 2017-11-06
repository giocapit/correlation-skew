#ifndef NbaskeOption_hpp
#define NbaskeOption_hpp
#include "Equity.hpp"
#include "Nbasket.hpp"
#include "Option.hpp"

class NbasketOption: public Option
{
	public:

		NbasketOption():Option(){};
		NbasketOption(double expiry_, Nbasket *basket_, double strike_,type cp_):
			Option(expiry_, basket_,  strike_, cp_){};
		
		~NbasketOption();

		double payoff(double spotIndex) const;

};
#endif
