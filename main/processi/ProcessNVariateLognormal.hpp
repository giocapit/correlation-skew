#ifndef procNVar_Lognormal_Abs_hpp
#define procNVar_Lognormal_Abs_hpp
#include "Process.hpp"
#include <vector>

class ProcessNVariateLognormal: public Process
{
	protected:
		size_t basket_size;
		std::vector<double> sigma;
		std::vector<std::vector<double>> rho;
	public:
		ProcessNVariateLognormal(size_t basket_size, std::vector<double> sigma, double rho);


		~ProcessNVariateLognormal(){};
		std::vector<double> * getSigma();
		std::vector<std::vector<double>> * getRho();

		void generaCammino(double T){};
		void generaCamminiOneShot(double T, int N){};
		double getAssetEvaluation(const Asset *asset, 
				double r,
				double T) const{return 0;};

};
#endif
