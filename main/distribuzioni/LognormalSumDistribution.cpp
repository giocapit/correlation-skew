#include <cmath>
#include "LognormalSumDistribution.hpp"


LognormalSumDistribution::LognormalSumDistribution(double r, double w1, double w2, double rho, double sigma1, double sigma2)
{
	this->r = r;
	this->w1 = w1;
	this->w2 = w2;
	this->rho = rho;
	this->sigma1 = sigma1;
	this->sigma2 = sigma2;
}

double LognormalSumDistribution::M1()
{
    return exp(r);
}

double LognormalSumDistribution::M2()
{

    return 2 * w1 * w2 * exp(2 * r + sigma1 * sigma2 * rho) +\
          pow(w1,2) * exp(2 * r + pow(sigma1,2)) +\
          pow(w2,2) * exp(2 * r + pow(sigma2,2));

}

double LognormalSumDistribution::M3()
{

    return pow(w1,3) * exp(3 * r + 3 * pow(sigma1,2)) +\
            3 * pow(w1,2) * w2 * exp(3 * r + pow(sigma1,2) + 2 * sigma1 * sigma2 * rho) +\
            3 * pow(w2,2) * w1 * exp(3 * r + pow(sigma2,2) + 2 * sigma1 * sigma2 * rho) +\
            pow(w2,3) * exp(3 * r + 3 * pow(sigma2,2));
}
