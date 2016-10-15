#include "BiVariateJumpDistribution.hpp"
#include <iostream>
#include <fstream>
#include <cmath>
#include <time.h>
#include <cstdlib>

using namespace std;
int main()
{
		double lambda1,lambda2,rho;
		lambda1 = 0;
		lambda2 = 0.7;
		rho = 0;
		int numTests = 1000000;
		int dim = 100;

		BiVariateJumpDistributionAntitetica X = BiVariateJumpDistributionAntitetica(lambda1/dim,lambda2/dim,rho,dim);
//		BiVariateJumpDistribution X = BiVariateJumpDistribution(lambda1/dim,lambda2/dim,rho);

		int a1;
		int a2;
		double sumPoisEul1=0;
		double sumPoisEul2=0;

//		ofstream miofile;
//		miofile.open("estrazioni_bivariata_salti");
		double sum_Pois1_quadro = 0;
		double sum_Pois2_quadro = 0;
		double sum_Pois1xPois2_quadro=0;
		srand (time(NULL));
	    for (int i=0; i< numTests; ++i)
	    {
			double A1=0;
			double A2=0;

	    	for (int j=0; j<dim; ++j)
	    	{
				X(a1,a2);
				A1 = A1 + a1;
				A2 = A2 + a2;
	    	}
	    	sumPoisEul1 = sumPoisEul1 + A1;
	    	sumPoisEul2 = sumPoisEul2 + A2;
			sum_Pois1_quadro = sum_Pois1_quadro + (A1 - lambda1)*(A1 - lambda1);
			sum_Pois2_quadro = sum_Pois2_quadro + (A2 - lambda2)*(A2 - lambda2);
			sum_Pois1xPois2_quadro = sum_Pois1xPois2_quadro + (A1 - lambda1)*(A2 - lambda2);
	    }
	    double p1 = sumPoisEul1/numTests;
	    double p2 = sumPoisEul2/numTests;
	    double sigma1 = sqrt(sum_Pois1_quadro/numTests);
	    double sigma2 = sqrt(sum_Pois2_quadro/numTests);
	    double varianza = sum_Pois1xPois2_quadro/numTests;
	    double rho_campione = varianza/(sigma1*sigma2);

//	    miofile.close();
	    cout << "p1" << "		|" << "p2" << "		|" << "sigma1" << "		|" << "sigma2" << "		|" << "rho_campione" << "\n";
	    cout << p1 << "	|" << p2 << "	|" << sigma1 << "	|" << sigma2 << "	|" << rho_campione << "\n";
	    return 0;
}



