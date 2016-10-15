#include "NormalDistribution.hpp"
#include <iostream>
#include <cmath>



void testCumulativeNormalDistribution()
{
	     // Select a few input values
	    double x[] = 
    		{
       		 -3, 
       		 -1, 
        	0.0, 
        	0.5, 
        	2.1 
	    };
	    double y[] =
	    {
        	0.00134989803163, 
        	0.158655253931, 
        	0.5, 
        	0.691462461274, 
        	0.982135579437 
    		};

	    CumulativeNormalDistribution phi;
	    //phi = CumulativeNormalDistribution(0.0,1.0);

	    int numTests = sizeof(x)/sizeof(double);
	    double maxError = 0.0;

	    for (int i=0; i< numTests; ++i)
	    {
		    double error = fabs(y[i] - phi(x[i]));
		    if (error > maxError)
			    maxError = error;
	    }
		std::cout << "Maximum error: " << maxError << "\n";

}

int main()
{
	testCumulativeNormalDistribution();
	return 0;
}

