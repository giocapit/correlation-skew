#include "BernoulliDistribution.hpp"
#include "randomGenerator.hpp"
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <random>
#include <chrono>

using namespace std;


int main()
{
		double lambda;
		lambda = 0.7;
		unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
		generator.seed(seed);
		int numTests = 1000000;
		int dim = 300;

		BernoulliDistribution X = BernoulliDistribution(lambda/dim);
		int a;

		double sumPoisEul=0;

//		ofstream miofile;
//		miofile.open("estrazioni_bivariata_salti");
		double sum_Pois_quadro = 0;

	    for (int i=0; i< numTests; ++i)
	    {
			double A=0;

	    	for (int j=0; j<dim; ++j)
	    	{

				a = X();
				A = A + double(a);
	    	}
	    	sumPoisEul = sumPoisEul + A;
			sum_Pois_quadro = sum_Pois_quadro + (A - lambda)*(A - lambda);
	    }
	    double p = sumPoisEul/numTests;
	    double sigma = sqrt(sum_Pois_quadro/numTests);

//	    miofile.close();
	    cout << "p" << "		|" << "sigma"  << "\n";
	    cout << p <<  "	|" << sigma << "\n";

		BernoulliDistribution Y = BernoulliDistribution(lambda/dim);
		sumPoisEul=0;
	    sum_Pois_quadro = 0;

	    for (int i=0; i< numTests; ++i)
	    {
			double A=0;

	    	for (int j=0; j<dim; ++j)
	    	{

				a = Y();
				A = A + double(a);
	    	}
	    	sumPoisEul = sumPoisEul + A;
			sum_Pois_quadro = sum_Pois_quadro + (A - lambda)*(A - lambda);
	    }
	    p = sumPoisEul/numTests;
	    sigma = sqrt(sum_Pois_quadro/numTests);

//	    miofile.close();
	    cout << "p" << "		|" << "sigma"  << "\n";
	    cout << p <<  "	|" << sigma << "\n";


	    return 0;
}



