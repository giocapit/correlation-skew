#include "ProcessBiVariateLognormal.hpp"

#include <cmath>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>
#ifdef stampaW1W2
#include <iostream>
#endif
#ifdef STAMPA_CAMMINI
#include <fstream>
#endif

void ProcessBiVariateLognormal::generaCammino(double T)
{
//	Z1[maxContatore].push_back((*((NormalDistributionAntitetica*)(N1)))());
//	Z2[maxContatore].push_back((*((NormalDistributionAntitetica*)(N2)))());
	Z1[maxContatore].push_back((*N1)());
	Z2[maxContatore].push_back((*N2)());
#ifdef STAMPA_CAMMINI
	ofstream miofile;
	miofile.open("C:\\Users\\Giovanni\\Dropbox\\mip\\project_work\\Dati_e_eseguibili\\dump.csv",std::ios_base::app);
	for (int i=0;i<dim;i++)
	{
		miofile << Z1[maxContatore][i] << ";"  ;
	}
	miofile << "\n";
	for (int i=0;i<dim;i++)
	{
		miofile << Z2[maxContatore][i] << ";"  ;
	}
	miofile << "\n";
	miofile.flush();
	miofile.close();
#endif
	maxContatore = maxContatore+1;
};

void ProcessBiVariateLognormal::generaCamminiOneShot(double T, int N)
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
	}
	gsl_rng_free(rand);
}

double ProcessBiVariateLognormal::getAssetEvaluation(const Asset *asset, 
					double r, 
					double T) const
{

	Basket* basket = (Basket*) asset;
#ifdef stampaW1W2
	std::cout << W1 << " " << Z2[contatore][0] << "\n";
#endif
	double w1 = basket -> get_w1();
	double w2 = basket -> get_w2();

	double W1 = Z1[contatore][0];
	double W2 = rho * W1 + sqrt(1-rho*rho) * Z2[contatore][0];

	double I1 = exp((r - 0.5 * sigma1 * sigma1) * T + sigma1 * sqrt(T) * W1);
	double I2 = exp((r - 0.5 * sigma2 * sigma2) * T + sigma2 * sqrt(T) * W2);

	double nuovoIndice = I1 * w1 + I2 * w2;
	return nuovoIndice;
}
;
