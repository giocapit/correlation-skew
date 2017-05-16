#include "bsformula.hpp"
#include "BSPricer.hpp"
#include "LognormalDistribution.hpp"
#include <iostream>
#include <cmath>
#include <boost/scoped_ptr.hpp>
#include <boost/shared_ptr.hpp>


void testbsFormula()
{
	     // Select a few input values
	    double S0[] = 
    		{
       		 100,150, 1
	    };

	    double K[] = 
    		{
       		 120, 150*1.3, 0.7
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
		    LogNormalDistribution* phi = new LogNormalDistribution(0, r[i] - 0.5 * pow(sigma[i],2), sigma[i]);

		    double price = bsprice(S0[i], K[i], r[i], T[i], sigma[i], 0, 1);

			BSPricer pricer(phi);
		    double price1 = pricer.bsformula(r[i], T[i], K[i]/S0[i]);
		    double error = fabs(y[i] - price);
		    if (error > maxError)
			    maxError = error;
		    std::cout << "price: " << price << " price1 " << price1 << "\n";
	    }
		std::cout << "Maximum error: " << maxError << "\n";

}

int main()
{
	testbsFormula();
	return 0;
}


