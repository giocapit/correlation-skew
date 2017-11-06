#include "NbasketOption.hpp"
#include <algorithm>



NbasketOption::~NbasketOption(){};
double NbasketOption::payoff(double spotIndex) const
{
	double pOff = std::max(cp * (spotIndex - strike) ,0.0) * ((Nbasket*)underlying) -> getMultiplier();
	return pOff;
}
