#include "BiVariateJumpDistribution.hpp"
#include "randomGenerator.hpp"
#include <cstdlib>
#include <cmath>
//#include <iostream>

BiVariateJumpDistribution::BiVariateJumpDistribution(double lambda1_,
		double lambda2_, double rho_)
{
	lambda1 = lambda1_;
	lambda2 = lambda2_;
	rho = rho_;

	//si partiziona l'intervallo unitario in 4 segmenti di lunghezza proporzionale alla probabilità degli eventi elementari:
	// - p00 -> probabilità che non si verifichi alcun salto
	// - p10 -> probabilità che X1 salti e X2 non salti
	// - p01 -> probabilità che X1 non salti e X2 salti
	// - p11 -> probabilità che sia X1 che X2 abbiano un salto
	// i 4 coefficienti calcolati sotto sono:
	// P11 = p11
	// P10 = p11 + p10
	// P01 = p11 + p10 + p01
	// P00 = p00 + p10 + p01 + p11 = 1
	P11 = rho * sqrt((lambda1 - lambda1*lambda1)*(lambda2 - lambda2*lambda2))
								+ lambda1 * lambda2;
	P10 = lambda1;
	P01 = lambda1 + lambda2 - P11;
	P00 = 1;
}

BiVariateJumpDistribution::~BiVariateJumpDistribution() {
}

int BiVariateJumpDistribution::operator ()(int& x1, int& x2)
{
	//double x = rand()/static_cast<double>(RAND_MAX);
	double x = randUniform(generator);
	if (x < P11)
	{
		x1 = 1;
		x2 = 1;
		return 0;
	} else if(x < P10){
		x1 = 1;
		x2 = 0;
		return 0;
	} else if(x < P01){
		x1 = 0;
		x2 = 1;
		return 0;
	}
	x1 = 0;
	x2 = 0;
	return 0;
}


int BiVariateJumpDistributionAntitetica::operator ()(int& x1, int& x2)
{
	double x;
	if(pari)
	{
		//x = rand()/static_cast<double>(RAND_MAX);
		x = randUniform(generator);
		estrazioniPassate[k] = x;
	}else
	{
		x = 1 - estrazioniPassate[k];
	}
	if (x < P11)
	{
		x1 = 1;
		x2 = 1;
		k++;
		if(k==dim)
		{
			k=0;
			pari = !pari;
		}
		return 0;
	} else if(x < P10){
		x1 = 1;
		x2 = 0;
		k++;
		if(k==dim)
		{
			k=0;
			pari = !pari;
		}
		return 0;
	} else if(x < P01){
		x1 = 0;
		x2 = 1;
		k++;
		if(k==dim)
		{
			k=0;
			pari = !pari;
		}
		return 0;
	}
	x1 = 0;
	x2 = 0;
	k++;
	if(k==dim)
	{
		k=0;
		pari = !pari;
	}
	return 0;
}
