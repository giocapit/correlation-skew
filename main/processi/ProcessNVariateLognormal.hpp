#ifndef procNVar_Lognormal_Abs_hpp
#define procNVar_Lognormal_Abs_hpp
#include "Process.hpp"
#include <vector>

class ProcessNVariateLognormal: public Process
{
	protected:
		size_t basket_size;
		vector<double> sigma;
		vector<vector<double>> rho;
	public:
		ProcessNVariateLognormal(size_t basket_size, vector<double> sigma, double rho):
			Process();


		~ProcessNVariateLognormal(){};


};
#endif
