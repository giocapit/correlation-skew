#include <cmath>
//#include <stdio.h>
#include "LognormalDistribution.hpp"

using namespace std;
LogNormalDistribution::LogNormalDistribution(double tau, double m,double s)
{
	this->tau=tau;
	this->m=m;
	this->s=s;
};

double LogNormalDistribution::pdf(double x) const
{

        double y = (1 / (s * (x - tau) * sqrt(2 * M_PI))) * exp(-(pow(log(x - tau) - m, 2) / (2 * pow(s,2))));
    	return y;
};

void LogNormalDistribution::setParams(double tau, double m,double s)
{

};
double LogNormalDistribution::M1() const
{
	return M1(tau, m, s);
}

double LogNormalDistribution::M2() const
{
	return M2(tau, m, s);
}

double LogNormalDistribution::M3() const
{
	return M3(tau, m, s);
}

double LogNormalDistribution::M4() const
{
	return M4(tau, m, s);
}

double LogNormalDistribution::M5() const
{
	return M5(tau, m, s);
}

double LogNormalDistribution::M1(double tau, double m, double s)
{
	return tau + exp(m + 0.5 * pow(s,2));
};
double LogNormalDistribution::M2(double tau, double m, double s)
{
	return pow(tau,2) 
		+ 2 * tau * exp(m + 0.5 * pow(s,2)) 
		+ exp(2 * m + 2 * pow(s,2));
};
double LogNormalDistribution::M3(double tau, double m, double s)
{
	//printf("inputs for M3 are % .5e % .5e %.5e\n",tau, m, s);
	return pow(tau,3) 
		+ 3 * pow(tau,2) * exp(m + 0.5 * pow(s,2)) 
		+ 3 * tau * exp(2 * m + 2 * pow(s,2)) 
		+ exp(3 * m + 4.5 * pow(s,2));
};

double LogNormalDistribution::M4(double tau, double m, double s)
{
	return pow(tau,4)
	        + 4 * pow(tau,3) * exp(m + 0.5 * pow(s,2))
		+ 6 * pow(tau,2) * exp(2 * m + 2 * pow(s,2)) 
		+ 4 * tau *  exp(3 * m + 4.5 * pow(s,2))
		+ exp(4 * m + 8 * pow(s,2));
};

double LogNormalDistribution::M5(double tau, double m, double s)
{
	return pow(tau,5)
	        + 5 * pow(tau,4) * exp(m + 0.5 * pow(s,2))
		+ 10 * pow(tau,3) * exp(2 * m + 2 * pow(s,2)) 
		+ 10 * pow(tau,2) * exp(3 * m + 4.5 * pow(s,2)) 
		+ 5 * tau *  exp(4 * m + 8 * pow(s,2))
		+ exp(4 * m + 12.5 * pow(s,2));
};

double LogNormalDistribution::getTau() const
{
	return tau;
};
