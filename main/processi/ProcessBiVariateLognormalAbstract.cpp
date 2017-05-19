#include "ProcessBiVariateLognormalAbstract.hpp"


void ProcessBiVariateLognormalAbstract::setSigma1(double sigma)
{
	sigma1 = sigma;
}

void ProcessBiVariateLognormalAbstract::setSigma2(double sigma)
{
	sigma2 = sigma;
}
double ProcessBiVariateLognormalAbstract::getSigma1()
{
	return sigma1;
}
double ProcessBiVariateLognormalAbstract::getSigma2()
{
	return sigma2;
}
double ProcessBiVariateLognormalAbstract::getRho()
{
	return rho;
}
