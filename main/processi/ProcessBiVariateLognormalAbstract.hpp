#ifndef procBiVar_Lognormal_Abs_hpp
#define procBiVar_Lognormal_Abs_hpp
#include "ProcessBiVariate.hpp"
#include "Basket.hpp"

class ProcessBiVariateLognormalAbstract: public ProcessBiVariate
{
	protected:
		double sigma1;
		double sigma2;
		double rho;
	public:
		ProcessBiVariateLognormalAbstract(double sigma1_,double sigma2_,double rho_,int N):
			ProcessBiVariate(N)
		{
			sigma1 = sigma1_;
			sigma2 = sigma2_;
			rho = rho_;
		};

		ProcessBiVariateLognormalAbstract(double sigma1_,double sigma2_,double rho_,int N,int dim):
			ProcessBiVariate(N,dim)
		{
			sigma1 = sigma1_;
			sigma2 = sigma2_;
			rho = rho_;
		};

		ProcessBiVariateLognormalAbstract(ProcessBiVariate* p):ProcessBiVariate(p)
		{
			sigma1 = 0;
			sigma2 = 0;
			rho = 0;
		}

		ProcessBiVariateLognormalAbstract(double sigma1_,double sigma2_,double rho_,int N, NormalDistribution *N1_,
																							NormalDistribution *N2_):
			ProcessBiVariate(N,N1_,N2_)
		{
			sigma1 = sigma1_;
			sigma2 = sigma2_;
			rho = rho_;
		};

		ProcessBiVariateLognormalAbstract(double sigma1_,double sigma2_,double rho_,int N,int dim, NormalDistribution *N1_,
																									NormalDistribution *N2_):
			ProcessBiVariate(N,dim,N1_,N2_)
		{
			sigma1 = sigma1_;
			sigma2 = sigma2_;
			rho = rho_;
		};

		~ProcessBiVariateLognormalAbstract(){};

		void setRho(double rho_)
		{
			rho = rho_;
		}

		virtual void generaCammino(double T)=0;
		void generaCamminiOneShot(double T, int N){};
		virtual double getAssetEvaluation(const Asset *asset,
				double r,
				double T) const = 0;

		void setSigma1(double sigma);
		void setSigma2(double sigma);
		bool useEulerToCalculateCorrelation(){return false;}
		double getSigma1();
		double getSigma2();
		double getRho();

};
#endif
