#include "ProcessNVariateLognormal.hpp"
#include <utility>



ProcessNVariateLognormal::ProcessNVariateLognormal(size_t _basket_size, std::vector<double> _sigma,double _rho):
			Process(),
			basket_size(_basket_size),
			sigma (std::move(_sigma)),
			rho(_basket_size,std::vector<double> (_basket_size,_rho))
		{
			for (size_t i=0; i < basket_size; ++i)
			{
				rho[i][i] = 1;
			}
		};

std::vector<double> * ProcessNVariateLognormal::getSigma()
{
	return & sigma;
};

		std::vector<std::vector<double>> * ProcessNVariateLognormal::getRho()
{
	return & rho;
}
