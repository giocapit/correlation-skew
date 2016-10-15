#include "PoissonDistribution.hpp"
#include "randomGenerator.hpp"
#include <cmath>
#include <cstdlib>



#ifndef DIST_POIS_CPP
#define DIST_POIS_CPP

PoissonDistribution::PoissonDistribution(double lambda_)
{
	lambda = lambda_;
	if (lambda == 0)
	{
		funcPointer = &extractPoissonNull;
	}else{
		funcPointer = &extractPoisson;
	}
	
//  gsl_rng_env_setup();
//  Type = gsl_rng_default;
//  r = gsl_rng_alloc (Type);
}
PoissonDistribution::~PoissonDistribution()
{
//	gsl_rng_free (r);
}	

//int PoissonDistribution::operator()(double T) const
//{
//     	int k = gsl_ran_poisson (r, lambda*T);
//	return k;
//}

int PoissonDistribution::extractPoisson(double T)
{
//	double x = rand()/static_cast<double>(RAND_MAX);
	double x = randUniform(generator);
	double cumPoisson=0;
	int fattoriale = 1;
	for (int i = 0; true; i++)
	{
		double Pi = exp(-lambda * T) * pow(lambda * T,i)/fattoriale;
		fattoriale = fattoriale * (i+1);
		cumPoisson = cumPoisson + Pi;
		if (x < cumPoisson)
			return i;
	}
}

int PoissonDistribution::extractPoissonNull(double T)
{
	return 0;
}

int PoissonDistribution::operator()(double T)
{
	return (*this.*funcPointer)(T);
	
}

double PoissonDistributionAntitetica::operator ()(double T)
{
	int numeroEstratto;
	if(pari)
	{
		//double x = rand()/static_cast<double>(RAND_MAX);
		double x = randUniform(generator);
		double cumPoisson=0;
		int fattoriale = 1;
		for (int i = 0; true; i++)
		{
			double Pi = exp(-lambda * T) * pow(lambda * T,i)/fattoriale;
			fattoriale = fattoriale * (i+1);
			cumPoisson = cumPoisson + Pi;
			if (x < cumPoisson)
			{
				numeroEstratto = i;
				break;
			}
		}
		estrazioniPassate[k]=x;
		k++;
		if(k==dim)
		{
			k=0;
			pari = false;
		}
		return numeroEstratto;
	}else{
		double x = 1-estrazioniPassate[k];
		double cumPoisson=0;
		int fattoriale = 1;
		for (int i = 0; true; i++)
		{
			double Pi = exp(-lambda * T) * pow(lambda * T,i)/fattoriale;
			fattoriale = fattoriale * (i+1);
			cumPoisson = cumPoisson + Pi;
			if (x < cumPoisson)
			{
				numeroEstratto = i;
				break;
			}
		}

		k++;
		if(k==dim)
		{
			k=0;
			pari = true;
		}
		return numeroEstratto;
	}

}
#endif
