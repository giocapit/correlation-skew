#include "ProcessBiVariateJumpDiffusion.hpp"
#include <cmath>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>
#ifdef stampaW1W2
#include <iostream>
#endif

void ProcessBiVariateJumpDiffusion::generaCammino(double T)
{
	Z1[maxContatore].push_back((*N1)());
	Z2[maxContatore].push_back((*N2)());
	X1[maxContatore].push_back((*P1)(T));
	X2[maxContatore].push_back((*P2)(T));
	maxContatore = maxContatore+1;
};

void ProcessBiVariateJumpDiffusion::generaCamminiOneShot(double T, int N)
{
	
  const gsl_rng_type * Type;
  gsl_rng * rand;
  gsl_rng_env_setup();
  Type = gsl_rng_default;
  rand = gsl_rng_alloc (Type);
  maxContatore = N;
	for (int i = 0 ; i < N; i++)
	{
		Z1[i].push_back(gsl_ran_gaussian(rand , 1.0));
		Z2[i].push_back(gsl_ran_gaussian(rand , 1.0));
		X1[i].push_back(gsl_ran_poisson (rand, lambda1*T));
		X2[i].push_back(gsl_ran_poisson (rand, lambda2*T));
	}
	gsl_rng_free(rand);
}

double ProcessBiVariateJumpDiffusion::getAssetEvaluation(const Asset *asset, 
					double r, 
					double T) const
{

	Basket* basket = (Basket*) asset;
	double mu1 = r - lambda1 * (J1 - 1);
	double mu2 = r - lambda2 * (J2 - 1);
	double W1 = Z1[contatore][0];
	double W2 = rho * W1 + sqrt(1-rho*rho) * Z2[contatore][0];
#ifdef stampaW1W2
	std::cout << W1 << " " << Z2[contatore][0] << "---\n";
#endif
	double w1 = basket -> get_w1();
	double w2 = basket -> get_w2();
	double jumpComponent1 = log(J1) * X1[contatore][0];
	double jumpComponent2 = log(J2) * X2[contatore][0];

	double I1 = exp((mu1 - 0.5 * sigma1 * sigma1) * T + sigma1 * sqrt(T) * W1 + jumpComponent1);
	double I2 = exp((mu2 - 0.5 * sigma2 * sigma2) * T + sigma2 * sqrt(T) * W2 + jumpComponent2);

	double nuovoIndice = I1 * w1 + I2 * w2;
	return nuovoIndice;
}
;

void ProcessBiVariateJumpDiffusion::allocateRandomVariables(int N)
{
	ProcessBiVariate::allocateRandomVariables(N);
	X1 = new vector<int>[N];
	X2 = new vector<int>[N];
}
