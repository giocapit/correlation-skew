#include "ProcessBiVariateLognormalEulero.hpp"
#include <cmath>
#include <fstream>


void ProcessBiVariateLognormalEulero::generaCammino(double T)
{
	for (int i = 0 ; i < dim ; i++)
	{
		Z1[maxContatore].push_back((*N1)());
		Z2[maxContatore].push_back((*N2)());
	}
	maxContatore = maxContatore+1;

}

double ProcessBiVariateLognormalEulero::getAssetEvaluation(const Asset* asset,
		double r, double T) const
{

	Basket* basket = (Basket*) asset;
	double w1 = basket -> get_w1();
	double w2 = basket -> get_w2();

	double dt = T/dim;
	double I1 = 1;
	double I2 = 1;
	for (int i = 0; i< dim; i++)
	{
		double W1 = Z1[contatore][i];
		double W2 = rho * W1 + sqrt(1-rho*rho) * Z2[contatore][i];
		I1 = I1 * (1 + r * dt + sigma1 * sqrt(dt) * W1);
		I2 = I2 * (1 + r * dt + sigma2 * sqrt(dt) * W2);
	}
#ifdef STAMPA_CAMMINI
	ofstream miofile;
	miofile.open("C:\\Users\\Giovanni\\Dropbox\\mip\\project_work\\Dati_e_eseguibili\\dump.csv",std::ios_base::app);
	for (int i=0;i<dim;i++)
	{
		miofile << Z1[contatore][i] << ";"  ;
	}
	miofile << "\n";
	for (int i=0;i<dim;i++)
	{
		miofile << Z2[contatore][i] << ";"  ;
	}
	miofile << "\n";
	miofile.flush();
	miofile.close();
#endif

	double nuovoIndice = I1 * w1 + I2 * w2;
	return nuovoIndice;
}
;

