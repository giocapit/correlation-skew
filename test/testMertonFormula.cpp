#include "mertonFormula.hpp"
#include <iostream>
#include <cmath>



void testMertonFormula()
{
	     // Select a few input values
	    double S0[] = 
    		{
       		 150,150,100
	    };

	    double K[] = 
    		{
       		 133.234,195,130
	    };
	    double r[] = 
    		{
       		 0.03 ,0.03,0.03
	    };
	    double T[] = 
    		{
       		 0.5 , 1, 1
	    };
	    double lambda[] = 
    		{
       		 0.5 , 0.5, 0.3
	    };
	    
	    double J[] = 
    		{
       		 0.4 ,0.2,0.4
	    };
	    double sigma[] = 
    		{
       		 0.23 ,0.3,0.2
	    };
	    double y[] =
	    {
        	33.82191306,0 ,0
    		};


	    int numTests = sizeof(S0)/sizeof(double);
	    double maxError = 0.0;

	    for (int i=0; i< numTests; ++i)
	    {
	    	double price = mertonPrice(S0[i],
				    K[i],
				    r[i],
				    T[i],
				    lambda[i],
				    J[i],
				    sigma[i],1);
		    double error = fabs(y[i] - price);
		    if (error > maxError)
			    maxError = error;
			std::cout << "price: " << price << "\n";

	    }
		std::cout << "Maximum error: " << maxError << "\n";

}

int main()
{
	testMertonFormula();
	return 0;
}


