#include <cmath>
#include "LognormalDistribution.hpp"

double biVariateLognormalM1(double r, double w1, double w2, double rho, double sigma1, double sigma2)
{
    return math.exp(r)
}

double biVariateLognormalM2(double r,double w1,double w2,double rho,double sigma1,double sigma2)
{
    return 2 * w1 * w2 * math.exp(2 * r + sigma1 * sigma2 * rho) +\
          w1**2 * math.exp(2 * r + sigma1**2) +\
          w2**2 * math.exp(2 * r + sigma2**2)
}

double biVariateLognormalM3(double r, double w1, double w2, double rho, double sigma1, double sigma2)
{
    return w1**3 * math.exp(3 * r + 3 * sigma1 ** 2) +\
            3 * w1**2 * w2 * math.exp(3 * r + sigma1**2 + 2 * sigma1 * sigma2 * rho) +\
            3 * w2**2 * w1 * math.exp(3 * r + sigma2**2 + 2 * sigma1 * sigma2 * rho) +\
            w2**3 * math.exp(3 * r + 3 * sigma2 ** 2)
}
