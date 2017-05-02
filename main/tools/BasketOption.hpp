#ifndef BaskeOption_hpp
#define BaskeOption_hpp
#include "Equity.hpp"
#include "Basket.hpp"
#include "Option.hpp"

class BasketOption: public Option
{
	//private:
	//	Basket *underlying;
	public:

		BasketOption():Option(){};
		BasketOption(double expiry_, Basket *basket_, double strike_,type cp_):
			Option(expiry_, basket_,  strike_, cp_){};
	//{
	//	basket = basket_;
	//};
		~BasketOption();

		double payoff(double spotIndex) const;

};
#endif
