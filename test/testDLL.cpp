#include <stdio.h>
#include <windows.h>
#include "dll_interface.cpp"


int main(void)
{
	double Multiplier=12;
	double riskFree=0.3;
	double lambda1 =0.2;
	double J1 =0.1;
	double sigma1 =0.3;
	double lambda2 =0.3;
	double J2 =0.3;
	double sigma2=0.3 ;
	double rho_merton=0.3 ;
	double w1=0.3 ;
	double w2 =0.7;
	double T =1;
	int num_strikes=3;
	double strikes[]={0.70,0.71,0.72,0.73,0.74,0.75,0.76,0.77,0.78,0.79,0.80,0.81,0.82,0.83,0.84,0.85,0.86,0.87,0.88,0.89,0.90,0.91,0.92,0.93,0.94,0.95,0.96,0.97,0.98,0.99,1.00,1.01,1.02,1.03,1.04,1.05,1.06,1.07,1.08,1.09,1.10,1.11,1.12,1.13,1.14,1.15,1.16,1.17,1.18,1.19,1.20,1.21,1.22,1.23,1.24,1.25,1.26,1.27,1.28,1.29,1.30};
	double result[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

	double* vba_Multiplier=&Multiplier;
	double* vba_riskFree= &riskFree;
	double* vba_lambda1= &lambda1 ;
	double* vba_J1= &J1;
	double* vba_sigma1= &sigma1 ;
	double* vba_lambda2= &lambda2;
	double* vba_J2= &J2;
	double* vba_sigma2= &sigma2;
	double* vba_rho_merton= &rho_merton;
	double* vba_w1= &w1;
	double* vba_w2= &w2;
	double* vba_T= &T;
	int* vba_num_strikes= &num_strikes;
	Interface_Implied_Correlation(
			// dati di mercato
			//
			 vba_Multiplier,
			 vba_riskFree,
			 vba_lambda1 ,
			 vba_J1 ,
			 vba_sigma1 ,
			 vba_lambda2 ,
			 vba_J2 ,
			 vba_sigma2 ,
			 vba_rho_merton ,
			 vba_w1 ,
			 vba_w2 ,
			 vba_T ,
			 vba_num_strikes,
			 strikes,
			 result
	);

        return 0;
}
