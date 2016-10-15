#include "ProcessJumpDiffusion.hpp"
#include "ProcessBiVariateJumpDiffusion.hpp"
#include "ProcessBiVariateJumpDiffusionWithCorrelatedJumps.hpp"
#include "calculateCorrelationSkew.hpp"


void calculateCorrelationSkewJumpDiffusion(	double multiplier,
													double riskFree,
													double lambda1 ,
													double J1 ,
													double sigma1 ,
													double lambda2 ,
													double J2 ,
													double sigma2 ,
													double rho_merton ,
													double w1 ,
													double w2 ,
													double T ,
													int num_strikes,
													double*  strikesArr ,
													double* results,
													int Nsim_
												)
{
	vector<double> strikes(num_strikes);
	vector<double> vols1(num_strikes);
	vector<double> vols2(num_strikes);

	for (int i=0; i<num_strikes ; i++)
	{
		strikes[i]= strikesArr[i];
	}

	Equity stock1 = Equity (multiplier);
	stock1.initializeVolatilitySurface(strikes);

	Equity stock2 = Equity (multiplier);
	stock2.initializeVolatilitySurface(strikes);

	ProcessJumpDiffusion process1 = ProcessJumpDiffusion(lambda1,J1,sigma1);
	stock1.calculateVolatilitySurface(&process1, T, riskFree);
	ProcessJumpDiffusion process2 = ProcessJumpDiffusion(lambda2,J2,sigma2);
	stock2.calculateVolatilitySurface(&process2, T, riskFree);

	Basket basket = Basket(&stock1,&stock2,w1,w2);
	int Nsim = Nsim_;
	ProcessBiVariateJumpDiffusion p = ProcessBiVariateJumpDiffusion( lambda1,
			J1,
			sigma1,
			lambda2,
			J2,
			sigma2,
			rho_merton,
			Nsim);
	basket.calculateCorrelationSurface(&p,T,riskFree,Nsim);
	for(int i = 0; i < num_strikes; i++)
	{
		results[i] = basket.getImpliedCorrelation(i);
	}

}


void calculateCorrelationSkewJumpDiffusionWithCorrelatedJumps(	double multiplier,
													double riskFree,
													double lambda1 ,
													double J1 ,
													double sigma1 ,
													double lambda2 ,
													double J2 ,
													double sigma2 ,
													double rho_diffusion ,
													double rho_jumps ,
													double w1 ,
													double w2 ,
													double T ,
													int num_strikes,
													vector<double> strikes ,
													vector<double>& results,
													int Nsim_,
													int dim
												)
{
	vector<double> vols1(num_strikes);
	vector<double> vols2(num_strikes);

	Equity stock1 = Equity (multiplier);
	stock1.initializeVolatilitySurface(strikes);

	Equity stock2 = Equity (multiplier);
	stock2.initializeVolatilitySurface(strikes);

	ProcessJumpDiffusion process1 = ProcessJumpDiffusion(lambda1,J1,sigma1);
	stock1.calculateVolatilitySurface(&process1, T, riskFree);
	ProcessJumpDiffusion process2 = ProcessJumpDiffusion(lambda2,J2,sigma2);
	stock2.calculateVolatilitySurface(&process2, T, riskFree);

	Basket basket = Basket(&stock1,&stock2,w1,w2);
	int Nsim = Nsim_;
	ProcessBiVariateJumpDiffusionWithCorrelatedJumps p = ProcessBiVariateJumpDiffusionWithCorrelatedJumps( lambda1,
			J1,
			sigma1,
			lambda2,
			J2,
			sigma2,
			rho_diffusion,
			rho_jumps,
			Nsim,
			dim);
	basket.calculateCorrelationSurface(&p,T,riskFree,Nsim);
	for(int i = 0; i < num_strikes; i++)
	{
		results[i] = basket.getImpliedCorrelation(i);
	}

}

