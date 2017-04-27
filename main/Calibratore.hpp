#include "Process.hpp"
#include "Equity.hpp"
#include <cstdlib>
#include <vector>


struct calibDataCorrelationSkew2
{
	size_t n;
	std::vector<double> y;
	std::vector<double> K;
	double multiplier;
	double T;
	double riskFree;
	double lambda1;
	double J1;
	double sigma1;
	double lambda2;
	double J2;
	double sigma2;
	double w1;
	double w2;

};

std::vector<double> calibraCorrelationSkew2(std::vector<double> initParams,
		std::vector<double>& y,
		std::vector<double>& K,
		double multiplier,
		double horiz,
		double riskFree,
		double lambda1,
		double J1,
		double sigma1,
		double lambda2,
		double J2,
		double sigma2,
		double w1,
		double w2);
