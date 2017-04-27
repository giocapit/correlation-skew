#include "calculateCorrelationSkew.hpp"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <string>
#include <time.h>


using namespace std;

int main (int argc,char* argv[])
{
	if (argc < 1) { // Check the value of argc. If not enough parameters have been passed, inform user and exit.
		std::cout << "Usage is ...\n"; // Inform the user of how to use the program
		std::cin.get();
		exit(0);
	} else { // if we got enough parameters...
		double Multiplier=100;
		double riskFree=0.03;
		double lambda1 =0.3;
		double J1 =0.4;
		double sigma1 =0.2;
		double lambda2 =0.5;
		double J2 =0.2;
		double sigma2=0.3 ;
		double rho_merton=0.5 ;
		double w1=0.3 ;
		double w2 =0.7;
		double T =1;
		int num_strikes=61;
		double strikes[]={0.70,0.71,0.72,0.73,0.74,0.75,0.76,0.77,0.78,0.79,0.80,0.81,0.82,0.83,0.84,0.85,0.86,0.87,0.88,0.89,0.90,0.91,0.92,0.93,0.94,0.95,0.96,0.97,0.98,0.99,1.00,1.01,1.02,1.03,1.04,1.05,1.06,1.07,1.08,1.09,1.10,1.11,1.12,1.13,1.14,1.15,1.16,1.17,1.18,1.19,1.20,1.21,1.22,1.23,1.24,1.25,1.26,1.27,1.28,1.29,1.30} ;
		double result[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
		int Nsim = 1000000;

		std::cout << argv[0];
		for (int i = 1; i < argc; i++) { /* We will iterate over argv[] to get the parameters stored inside.
		 * Note that we're starting on 1 because we don't need to know the
		 * path of the program, which is stored in argv[0] */
			string arg = string(argv[i]);
			if (i + 1 != argc)
			{// Check that we haven't finished parsing already
				if (arg == "-riskFree") {
					// We know the next argument *should* be the filename:
					riskFree = atof(argv[i + 1]);
				} else if (arg == "-l1") {
					lambda1 = atof(argv[i + 1]);
				} else if (arg == "-J1") {
					J1 = atof(argv[i + 1]);
				} else if (arg == "-s1") {
					sigma1 = atof(argv[i + 1]);
				} else if (arg == "-l2") {
					lambda2 = atof(argv[i + 1]);
				} else if (arg == "-J2") {
					J2 = atof(argv[i + 1]);
				} else if (arg == "-s2") {
					sigma2 = atof(argv[i + 1]);
				} else if (arg == "-rho") {
					rho_merton = atof(argv[i + 1]);
				} else if (arg == "-w1") {
					w1 = atof(argv[i + 1]);
				} else if (arg == "-w2") {
					w2 = atof(argv[i + 1]);
				} else if (arg == "-T") {
					T = atof(argv[i + 1]);
				} else if (arg == "-Nsim") {
					Nsim = atof(argv[i + 1]);
				} else {
					std::cout << "Not enough or invalid arguments, please try again.\n";
					exit(0);
				}
			std::cout << argv[i] << " ";
			}
			i = i +1;
		}

		//srand (time(NULL));
		// Dichiarazioni variabili
		//
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
				Nsim
		);
		ofstream miofile;
		//miofile.open("C:\\Users\\Giovanni\\Dropbox\\mip\\project_work\\Dati_e_eseguibili\\risultatiSalti.csv"/*,std::ios_base::app*/);
		miofile.open("/home/giovanni/projects/correlation-skew/build/risultatiSalti.csv"/*,std::ios_base::app*/);
		for (int i = 0 ; i <num_strikes;i++)
		{
			miofile << setprecision(11) << result[i] << "\n";
		}
		miofile.close();

		return 0;
	}
}
