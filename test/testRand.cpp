#include <iostream>
#include <fstream>
#include <cmath>
#include <time.h>
#include <cstdlib>
#include <random>
#include <chrono>
#include "randomGenerator.hpp"

using namespace std;
void testRand(int numTests)
{
		srand (time(NULL));
		unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
		generator.seed(seed);

		//double a = 0;
		//p = &a;
		//int numTests = 100;
		int dim = 64;
		double a;
//		ofstream miofile;
//		miofile.open("estrazioni_normale");
		double sommaPoisson = 0;
	    for (int i=0; i< numTests; ++i)
	    {
		double Poisson = 0;
	    	for (int j=0; j<dim;++j)
	    	{
				a = rand()/static_cast<double>(RAND_MAX);
				//a = randUniform(generator);
				if (a < 0.5/dim)
					Poisson = Poisson + 1;
	    	}
//		    miofile << a << " ";
	    	sommaPoisson = sommaPoisson + Poisson;
	    }
//	    miofile.close();
	    double mediaPoisson = sommaPoisson/numTests;
	    cout << mediaPoisson << "\n";
	    cout << RAND_MAX << "\n";
	    cout << generator.max() << "\n";


}

int main()
{
	int N = 1000000;
	testRand(N);
	return 0;
}

