#include "ProcessBiVariateJumpDiffusionWithCorrelatedJumps.hpp"
#include <vector>
#include <iostream>

using namespace std;
void testCalibrazioneProcessWithCorrelatedJumps(void)
{
	double strikestmp[] = {0.80,0.90,1.00,1.10,1.20};
	vector<double> strikes(5);
	double corrstmp[] = {0.71,0.62,0.54,0.47,0.45};
//{0.179328918,0.206672668,0.22859954834,0.24327850342,0.253456116};
	vector<double> corrs(5);

	for (int i=0; i<5 ; i++)
	{
		corrs[i]=corrstmp[i];
		strikes[i]= strikestmp[i];
	}

	CorrelationSurfaceSkew *corrSkew = new CorrelationSurfaceSkew(strikes,corrs);
	Basket basket = Basket (100.0,0.5,0.5,corrSkew);

	ProcessBiVariateJumpDiffusionWithCorrelatedJumps process = ProcessBiVariateJumpDiffusionWithCorrelatedJumps(0.09,
																						0.4,
																						0.2,
																						0.15,
																						0.2,
																						0.3,
																						0.30,
																						0.75,
																						0,
																						0);
	process.calibra(basket, 0.005, 1.0);

       	//double *pars = process.getParameters();
	double rhoDiff = process.getRhoDiffusion();
    double rhoJump = process.getRhoJump();
	std::cout << rhoDiff << "\n" << rhoJump <<  "\n";
}

int main()
{
	testCalibrazioneProcessWithCorrelatedJumps();
	return 0;
}
