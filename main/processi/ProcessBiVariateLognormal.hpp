#include "ProcessBiVariateLognormalAbstract.hpp"
#include "Basket.hpp"

class ProcessBiVariateLognormal: public ProcessBiVariateLognormalAbstract
{
	public:
		ProcessBiVariateLognormal(double sigma1_,double sigma2_,double rho_,int N):
			ProcessBiVariateLognormalAbstract(sigma1_,sigma2_,rho_,N)
		{
		};

		ProcessBiVariateLognormal(double sigma1_,double sigma2_,double rho_,int N,int dim):
			ProcessBiVariateLognormalAbstract(sigma1_,sigma2_,rho_,N,dim)
		{
		};

		ProcessBiVariateLognormal(ProcessBiVariate* p):ProcessBiVariateLognormalAbstract(p)
		{
		}

		ProcessBiVariateLognormal(double sigma1_,double sigma2_,double rho_,int N, NormalDistribution *N1_,
																					NormalDistribution *N2_):
			ProcessBiVariateLognormalAbstract(sigma1_,sigma2_,rho_,N, N1_, N2_)
		{
		};

		ProcessBiVariateLognormal(double sigma1_,double sigma2_,double rho_,int N,int dim, NormalDistribution *N1_,
																							NormalDistribution *N2_):
			ProcessBiVariateLognormalAbstract(sigma1_,sigma2_,rho_,N,dim, N1_, N2_)
		{
		};

		~ProcessBiVariateLognormal(){};

		void setRho(double rho_)
		{
			rho = rho_;
		}
		
		void generaCammino(double T);
		void generaCamminiOneShot(double T, int N);
		double getAssetEvaluation(const Asset *asset, 
				double r,
				double T) const;

};
		
