#include "../main/NormalDistribution.hpp"
#include <iostream>
#include <fstream>
#include <cmath>


using namespace std;
void testBoxMuller(int numTests)
{

		//double a = 0;
		//p = &a;
		NormalDistribution N = NormalDistribution();
		//int numTests = 100;
		double a[numTests];
		double *p;
		p = a;
		ofstream miofile;
		miofile.open("estrazioni_normale");

	    for (int i=0; i< numTests; ++i)
	    {
		    p[i] = N();
		    miofile << p[i] << " ";
	    }
	    miofile.close();


}

int main()
{
	int N = 10000;
	testBoxMuller(N);
	return 0;
}



