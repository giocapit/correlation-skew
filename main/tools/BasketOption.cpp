#include "BasketOption.hpp"
#include <algorithm>



BasketOption::~BasketOption(){};
double BasketOption::payoff(double spotIndex) const
{
	double pOff = std::max(cp * (spotIndex - strike) ,0.0) * ((Basket*)underlying) -> getMultiplier();
	return pOff;
}

