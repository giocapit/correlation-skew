#include "RectanglesIntegral.hpp"

double RectanglesIntegral::integrate(const std::function<double(double)>& integrand, 
				double a,
				double b)
{
	double integral = 0;
	double h = (b - a)/n;

	for (int i = 0; i < n; i++)
	{
		integral += integrand(a + i * h);
	}
	return integral * h;


}

