#include "NormalDistribution.hpp"
#include "randomGenerator.hpp"
#include <cmath>
#include <cstdlib>

#ifndef DIST_NORM_CPP
#define DIST_NORM_CPP

NormalDistribution::NormalDistribution(double mu_, double sigma_){
	mu = mu_;
	sigma = sigma_;
}

double NormalDistribution::operator()()
{
	double numeroEstratto = getNormalByBoxMuller();
	return numeroEstratto;
}

double NormalDistribution::getNormalByBoxMuller() const
{
	double u;
	double v;

	double rQuadro;
	
	do 
	{
		u = 2 * (randUniform(generator)) - 1;
		v = 2 * (randUniform(generator)) - 1;
		rQuadro = u*u + v*v;
	} while (rQuadro > 1);

	double numeroEstratto = u * sqrt(-2 * log(rQuadro)/rQuadro);
	return numeroEstratto;

}



CumulativeNormalDistribution::CumulativeNormalDistribution(double mu, double sigma){
	mu_ = mu;
	sigma_ = sigma;
}

double CumulativeNormalDistribution::operator()(double x) const {
	//costanti
	double a1 =  0.254829592;
    	double a2 = -0.284496736;
    	double a3 =  1.421413741;
    	double a4 = -1.453152027;
    	double a5 =  1.061405429;
    	double p  =  0.3275911;

	int sign = 1;
	if (x < 0)
		sign= -1;
	x = fabs(x)/sqrt(2.0);

	double t = 1.0/(1.0 + p*x);
	double y =  1.0 - (((((a5*t + a4)*t) + a3)*t + a2)*t + a1)*t*exp(-x*x);

	return 0.5 * (1.0 + sign*y);
}

double NormalDistributionAntitetica::operator ()()
{
	double numeroEstratto;
	if(pari)
	{
		numeroEstratto = getNormalByBoxMuller();
		estrazioniPassate[i]=numeroEstratto;
		i++;
		if(i==dim)
		{
			i=0;
			pari = false;
		}
		return numeroEstratto;
	}else{
		numeroEstratto = -estrazioniPassate[i];
		i++;
		if(i==dim)
		{
			i=0;
			pari = true;
		}
		return numeroEstratto;
	}

}

#endif
