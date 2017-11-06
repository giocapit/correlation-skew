#include "ProcessNVariateLognormal.hpp"
#include <utility>



ProcessNVariateLognormal::ProcessNVariateLognormal(size_t _basket_size, vector<double> _sigma,duble _rho):
			Process(),
			basket_size(_basket_size),
			sigma (std::move(_sigma)),
			rho(vector<double> tmp(_rho, _basket_size) , _basket_size )
		{
			for (size_t i=0; ++i; i < basket_size)
			{
				rho[i][i] = 1;
			}
		};
