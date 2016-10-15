#include "Equity.hpp"
#include "ProcessJumpDiffusion.hpp"
#include <vector>
#include <iostream>

using namespace std;

void testCalculateVolatilitySurface()
{

	double lambda = 0.3;
	double J = 0.2;
	double sigma = 0.4;
	double riskFree = 0.03;
	double T = 1;
	double multiplier = 100;
	double strikestmp[] = {0.70,0.71,0.72,0.73,0.74,0.75,0.76,0.77,0.78,0.79,0.80,0.81,0.82,0.83,0.84,0.85,0.86,0.87,0.88,0.89,0.90,0.91,0.92,0.93,0.94,0.95,0.96,0.97,0.98,0.99,1.00,1.01,1.02,1.03,1.04,1.05,1.06,1.07,1.08,1.09,1.10,1.11,1.12,1.13,1.14,1.15,1.16,1.17,1.18,1.19,1.20,1.21,1.22,1.23,1.24,1.25,1.26,1.27,1.28,1.29,1.30};
	vector<double> strikes(61);

	for (int i=0; i<61 ; i++)
	{
		strikes[i]= strikestmp[i];
	}

	Equity stock = Equity (multiplier);
	stock.initializeVolatilitySurface(strikes);

	ProcessJumpDiffusion process = ProcessJumpDiffusion(lambda,J,sigma);
	stock.calculateVolatilitySurface(&process, T, riskFree);
	double vol;
	for (int i = 0 ; i<61; i++)
	{
		vol = stock.getImpliedVolatility(i);
		cout << vol << " ";

	}

}

int main()
{
	testCalculateVolatilitySurface();
	return 0;
}
