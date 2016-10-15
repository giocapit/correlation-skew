#include "PoissonDistribution.hpp"
#include "iostream"

int main()
{
	int a;
	int suma=0;
	double sumvar = 0;
	PoissonDistribution P = PoissonDistribution(0.3);
	for (int i = 0 ; i < 100000000; i++)
	{
		a = P(1.0);
		suma = suma + a;
		sumvar = (static_cast<double>(a)-0.3)*(static_cast<double>(a)-0.3)+sumvar;

	}
	double media = static_cast<double>(suma)/100000000.0;
	double var = sumvar/100000000.0;
	std::cout << media << " " << var <<"\n";
}
