#include "Option.hpp"
#include <algorithm>

double Option::getStrike() const
{
	return strike;
}


double Option::getExpiry()const
{
	return expiry;
}

double Option::payoff(double S) const
{
	return std::max(cp*(S-strike),0.0);
}

Asset* Option::getUnderlying() const
{
	return underlying;
}
