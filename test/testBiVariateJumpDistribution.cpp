#include "BiVariateJumpDistribution.hpp"
#include "randomGenerator.hpp"
#include <iostream>
#include <fstream>
#include <cmath>
#include <time.h>
#include <cstdlib>
#include <random>
#include <chrono>

using namespace std;
int main()
{
		double lambda1,lambda2,rho;
		unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
		generator.seed(seed);

		lambda1 = 0.4;
		lambda2 = 0.3;
		rho = 0.6;
		int numTests = 1000000;
		int dim = 100;
		//double a = 0;
		//p = &a;
//		BiVariateJumpDistribution X = BiVariateJumpDistribution(lambda1/dim,lambda2/dim,rho);
		BiVariateJumpDistributionAntitetica X = BiVariateJumpDistributionAntitetica(lambda1/dim,lambda2/dim,rho,dim);

		//int numTests = 100;
		int a1;
		int a2;

//		ofstream miofile;
//		miofile.open("estrazioni_bivariata_salti");
		double A1=0;
		double A2=0;
		double sum_a1_quadro = 0;
		double sum_a2_quadro = 0;
		double sum_a1xa2_quadro=0;

		for (int i=0; i< numTests; ++i)
	    {
	    	a1=0;
	    	a2=0;
	    	for (int j=0; j< dim; ++j)
	    	{
	    		int b1=0;
	    		int b2=0;
	    		X(b1,b2);
	    		a1=a1+b1;
	    		a2=a2+b2;
	    	}
		    A1 = A1 + a1;
		    A2 = A2 + a2;
		    sum_a1_quadro = sum_a1_quadro + (a1  - lambda1)*(a1  - lambda1);
		    sum_a2_quadro = sum_a2_quadro + (a2 - lambda2)*(a2 - lambda2);
		    sum_a1xa2_quadro = sum_a1xa2_quadro + (a1 - lambda1)*(a2 - lambda2);
	    }
	    double p1 = A1/numTests;
	    double p2 = A2/numTests;
	    double sigma1 = sqrt(sum_a1_quadro/numTests);
	    double sigma2 = sqrt(sum_a2_quadro/numTests);
	    double varianza = sum_a1xa2_quadro/numTests;
	    double rho_campione = varianza/(sigma1*sigma2);

//	    miofile.close();
	    cout << "p1" << "		|" << "p2" << "		|" << "sigma1" << "		|" << "sigma2" << "		|" << "rho_campione" << "\n";
	    cout << p1 << "	|" << p2 << "	|" << sigma1 << "	|" << sigma2 << "	|" << rho_campione << "\n";
	    return 0;
}



