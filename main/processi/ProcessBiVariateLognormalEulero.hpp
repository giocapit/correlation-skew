#include "ProcessBiVariateLognormalAbstract.hpp"

class ProcessBiVariateLognormalEulero: public ProcessBiVariateLognormalAbstract
{
public:

	ProcessBiVariateLognormalEulero(double sigma1_,double sigma2_,double rho_,int N,int dim):
		ProcessBiVariateLognormalAbstract(sigma1_,sigma2_,rho_,N,dim)
	{
	};

	ProcessBiVariateLognormalEulero(double sigma1_,double sigma2_,double rho_,int N,int dim, NormalDistribution *N1_,
																						NormalDistribution *N2_):
		ProcessBiVariateLognormalAbstract(sigma1_,sigma2_,rho_,N,dim, N1_, N2_)
	{
	};

	ProcessBiVariateLognormalEulero(ProcessBiVariate* p):ProcessBiVariateLognormalAbstract(p){};

	~ProcessBiVariateLognormalEulero(){};

	void generaCammino(double T);

	double getAssetEvaluation(const Asset *asset,
			double r,
			double T) const;
	bool useEulerToCalculateCorrelation(){return true;}

};
