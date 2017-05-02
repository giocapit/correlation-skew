#include <cmath>
#include "LognormalDistribution.hpp"

double biVariateLognormalM1(double r, double w1, double w2, double rho, double sigma1, double sigma2)
{
    return exp(r);
}

double biVariateLognormalM2(double r,double w1,double w2,double rho,double sigma1,double sigma2)
{
    return 2 * w1 * w2 * exp(2 * r + sigma1 * sigma2 * rho) +\
          pow(w1,2) * exp(2 * r + pow(sigma1,2)) +\
          pow(w2,2) * exp(2 * r + pow(sigma2,2));
}

double biVariateLognormalM3(double r, double w1, double w2, double rho, double sigma1, double sigma2)
{
    return pow(w1,3) * exp(3 * r + 3 * pow(sigma1,2)) +\
            3 * pow(w1,2) * w2 * exp(3 * r + pow(sigma1,2) + 2 * sigma1 * sigma2 * rho) +\
            3 * pow(w2,2) * w1 * exp(3 * r + pow(sigma2,2) + 2 * sigma1 * sigma2 * rho) +\
            pow(w2,3) * exp(3 * r + 3 * pow(sigma2,2));
}
