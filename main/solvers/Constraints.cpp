#include "Constraints.hpp"
#include <cmath>
std::vector<double> Constraints::update(std::vector<double> x)
{
	std::vector<double> X = x;
	for (size_t i = 0; i < index.size(); i++)
	{
		X[i] = (upperBound[i] + lowerBound[i])/2 + atan(x[i]) * 
			((upperBound[i] - lowerBound[i])/M_PI);
	}
	return X;

};
