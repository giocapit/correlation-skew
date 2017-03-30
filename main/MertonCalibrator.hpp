#include "Process.hpp"
#include "Equity.hpp"
#include <cstdlib>
#include <vector>


struct calibData 
{
	size_t n;
	std::vector<double> y;
	std::vector<double> K;
	double S0;
	double T;
	double r;
};

std::vector<double> calibraMerton(std::vector<double> parToCalibrate, 
		std::vector<double>& y, 
		std::vector<double>& K, 
		double S0,
		double T,
		double r);

