#include "froot.hpp"
#include <cmath>

using namespace std;
double froot(Functional* f,double x_lower,double x_upper)
{
	double x = bisection(f, x_lower, x_upper);
	return x;
}

double bisection(Functional* f, double x_lower, double x_upper)
{
	double x=0;
	const double xtol = 1e-5;
	double f_x_upper;
	double f_x;
	f_x_upper = (*f)(x_upper);
	while(abs(x_upper - x_lower) > xtol)
	{
		x = (x_upper + x_lower)/2;
		f_x = (*f)(x);

		if(f_x_upper * f_x>0)
		{
			x_upper = x;
 			f_x_upper = f_x;
		} else{
			x_lower = x;
		}
	}

	return x;

}

double corde(Functional* f, double x_lower, double x_upper, double xtol)
{
	double f_x_lower = (*f)(x_lower);
    double f_x_upper = (*f)(x_upper);
	double x=0;
	double f_x=0;
	while((abs(x_upper - x_lower) > xtol) & (f_x!=0))
	{
		x = x_upper - f_x_upper * (x_upper - x_lower)/(f_x_upper - f_x_lower);
		f_x = (*f)(x);
    
    		if(f_x*f_x_lower < 0)
		{
        		x_upper = x;
        		f_x_upper = f_x;
		}else{
				x_lower = x;
				f_x_lower = f_x;
       }
}
return x;
}

double corde(Functional* f, double x_lower, double x_upper)
{
	const double xtol = 1e-5;
	double x = corde(f, x_lower, x_upper, xtol);
	return x;
}
