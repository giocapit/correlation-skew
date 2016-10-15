#include "calculateCorrelationSkew.hpp"
#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;


int main(void)
{
	double Multiplier=100;
	double riskFree=0.03;
	double lambda1 =0.3;
	double J1 =0.4;
	double sigma1 =0.2;
	double lambda2 =0.5;
	double J2 =0.2;
	double sigma2=0.3 ;
	double rho_merton=1 ;
	double w1=0.3 ;
	double w2 =0.7;
	double T =1;
	int num_strikes=61;
	double strikes[]={0.70,0.71,0.72,0.73,0.74,0.75,0.76,0.77,0.78,0.79,0.80,0.81,0.82,0.83,0.84,0.85,0.86,0.87,0.88,0.89,0.90,0.91,0.92,0.93,0.94,0.95,0.96,0.97,0.98,0.99,1.00,1.01,1.02,1.03,1.04,1.05,1.06,1.07,1.08,1.09,1.10,1.11,1.12,1.13,1.14,1.15,1.16,1.17,1.18,1.19,1.20,1.21,1.22,1.23,1.24,1.25,1.26,1.27,1.28,1.29,1.30} ;
	double result[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	calculateCorrelationSkewJumpDiffusion(
			// dati di mercato
			//
			 Multiplier,
			 riskFree,
			 lambda1 ,
			 J1 ,
			 sigma1 ,
			 lambda2 ,
			 J2 ,
			 sigma2 ,
			 rho_merton ,
			 w1 ,
			 w2 ,
			 T ,
			 num_strikes,
			 strikes,
			 result,
			 1000000
	);
	ofstream miofile;
	miofile.open("risultatiTest.dat");
	for (int i = 0 ; i <num_strikes;i++)
	{
		miofile << setprecision(11) << result[i] << "\n";
	}
	miofile.close();
	return 0;
}
