#include "bsformula.hpp"
#include <iostream>
#include <cmath>



void testbsFormula()
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
	    
	    double sigma[] = 
    		{
       		 0.3,0.3,0.05
	    };
	    double y[] =
	    {
        	6.2901991160551134,6.31151,32.0688
    		};


	    int numTests = sizeof(S0)/sizeof(double);
	    double maxError = 0.0;

	    for (int i=0; i< numTests; ++i)
	    {
		    double price = bsprice(S0[i], K[i], r[i], T[i], sigma[i], 0, 1);
		    double error = fabs(y[i] - price);
		    if (error > maxError)
			    maxError = error;
		    std::cout << "price: " << price << "\n";
	    }
		std::cout << "Maximum error: " << maxError << "\n";

}

int main()
{
	testbsFormula();
	return 0;
}


