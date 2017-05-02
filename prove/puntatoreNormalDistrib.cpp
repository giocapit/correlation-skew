#include "NormalDistribution.hpp"
#include <iostream>

using namespace std;

int main()
{
	double *p = nullptr ;
	//double a = 0;
	//*p=0.0;
	NormalDistribution N = NormalDistribution();
	//double a;
	//p = &a;
	*p = N();
	return 0;

}
