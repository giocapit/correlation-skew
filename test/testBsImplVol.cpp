#include "bsImplVol.hpp"
#include <iostream>
#include <cmath>



void testBsImplVol()
{
	     // Select a few input values
	    double S0[] =
    		{
       		 100,150, 100
	    };

	    double K[] =
    		{
       		 120, 150*1.3, 70
	    };
	    double r[] =
    		{
       		 0.03, 0.03 ,0.03
	    };
	    double T[] =
    		{
       		 1,1,1
	    };

	    double price[] =
	    {
        	6.2901991160551134,6.31151,32.0688
    		};

	    double sigma[] =
    		{
       		 0.3,0.3,0.05
	    };

	    int numTests = sizeof(S0)/sizeof(double);
	    double maxError = 0.0;

	    for (int i=0; i< numTests; ++i)
	    {
		    double vol = bsImplVol(S0[i], price[i], K[i], r[i], T[i]);
		    double error = fabs(sigma[i] - vol);
		    if (error > maxError)
			    maxError = error;
		    std::cout << "price: " << vol << "\n";
	    }
		std::cout << "Maximum error: " << maxError << "\n";

}

int main()
{
	testBsImplVol();
	return 0;
}


