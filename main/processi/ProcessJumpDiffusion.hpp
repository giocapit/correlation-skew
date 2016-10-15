#ifndef Proc_J_Diff_hpp
#define Proc_J_Diff_hpp
#include "Process.hpp"
#include "Equity.hpp"
#include <vector>

class ProcessJumpDiffusion : public Process
{
	private:
		double lambda;
		double J;
		double sigma;
	public:
		/*ProcessJumpDiffusion();*/
		ProcessJumpDiffusion(double lambda_ = 0.1, 
				double J_ = 0.1,
				double sigma_ = 0.1)
		{
			lambda = lambda_;
			J = J_;
			sigma = sigma_;
		}
				
		~ProcessJumpDiffusion(){};

		void generaCammino(double T);

		void generaCamminiOneShot(double T, int N){};
		double getAssetEvaluation(const Asset *asset, double r, double T) const;

		void calibra(Equity &asset, double riskFreeRate, double horiz);

		double* getParameters();

		double getLambda();
		double getJ();
		double getSigma();
};	
#endif
