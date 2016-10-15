#include <vector>

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
													int Nsim
												);

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
													std::vector<double> strikes ,
													std::vector<double>& results,
													int Nsim,
													int dim
												);
