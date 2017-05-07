#include <cmath>
#include "LognormalDistribution.hpp"

using namespace std;

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


		double LogNormalDistribution::M1(double tau, double m, double s)
{
    return tau + exp(m + 0.5 * pow(s,2));
};
		double LogNormalDistribution::M2(double tau, double m, double s)
{
    return pow(tau,2) + 2 * tau * exp(m + 0.5 * pow(s,2)) + exp(2 * m + 2 * pow(s,2));
};
		double LogNormalDistribution::M3(double tau, double m, double s)
{
    return pow(tau,3) + 3 * pow(tau,2) * exp(m + 0.5 * pow(s,2)) + 3 * tau * exp(2 * m + 2 * pow(s,2)) + exp(3 * m + 4.5 * pow(s,2));
};
