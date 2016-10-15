#include "ProcessBiVariateJumpDiffusionWithCorrelatedJumps.hpp"
#include "Calibratore.hpp"
#include <cmath>
#include <fstream>

void ProcessBiVariateJumpDiffusionWithCorrelatedJumps::generaCammino(double T)

{
	for (int i = 0 ; i < dim ; i++)
	{
		Z1[maxContatore].push_back((*N1)());
		Z2[maxContatore].push_back((*N2)());
		int tmpX1, tmpX2;
		(*X)(tmpX1,tmpX2);
		X1[maxContatore].push_back(tmpX1);
		X2[maxContatore].push_back(tmpX2);
	}
#ifdef STAMPA_CAMMINI
	ofstream miofile;
	miofile.open("C:\\Users\\Giovanni\\Dropbox\\mip\\project_work\\Dati_e_eseguibili\\dump.csv",std::ios_base::app);
	for (int i=0;i<dim;i++)
	{
		miofile << Z1[maxContatore][i] << ";"  ;
	}
	miofile << "\n";
	for (int i=0;i<dim;i++)
	{
		miofile << Z2[maxContatore][i] << ";"  ;
	}
	miofile << "\n";
	for (int i=0;i<dim;i++)
	{
		miofile << X1[maxContatore][i] << ";"  ;
	}
	miofile << "\n";
	for (int i=0;i<dim;i++)
	{
		miofile << X2[maxContatore][i] << ";"  ;
	}
	miofile << "\n";
	miofile.flush();
	miofile.close();
#endif

	maxContatore = maxContatore+1;


}

void ProcessBiVariateJumpDiffusionWithCorrelatedJumps::generaCamminiOneShot(
		double T, int N)
{
	  maxContatore = N;
		for (int i = 0 ; i < N; i++)
		{
			for (int j = 0; j < dim; j++)
			{
				Z1[i].push_back((*N1)());
				Z2[i].push_back((*N2)());
				int tmpX1, tmpX2;
				(*X)(tmpX1,tmpX2);
				X1[contatore].push_back(tmpX1);
				X2[contatore].push_back(tmpX2);
			}
		}
}

void ProcessBiVariateJumpDiffusionWithCorrelatedJumps::calibra(Basket& basket,
		double riskFreeRate, double T)
{
	CorrelationSurfaceSkew *corrSkew =(CorrelationSurfaceSkew*)basket.getImplCorrSurface();

	vector<double> *K = corrSkew -> getStrikes();
	vector<double> *corrs = corrSkew -> getCorrs();
	vector<double> initParams(2);
	initParams[0] = rho_diffusion;
	initParams[1] = rho_jump;

	vector<double> calibratedParams = calibraCorrelationSkew2(initParams,
			*corrs,
			*K,
			basket.getMultiplier(),
			T,
			riskFreeRate,
			lambda1,
			J1,
			sigma1,
			lambda2,
			J2,
			sigma2,
			basket.get_w1(),
			basket.get_w2());
	rho_diffusion = calibratedParams[0];
	rho_jump = calibratedParams[1];

}

double ProcessBiVariateJumpDiffusionWithCorrelatedJumps::getAssetEvaluation(
		const Asset* asset, double r, double T) const
{
	double dt = T/dim;
	Basket* basket = (Basket*) asset;
	double mu1 = r - lambda1 * (J1 - 1);
	double mu2 = r - lambda2 * (J2 - 1);
	double w1 = basket -> get_w1();
	double w2 = basket -> get_w2();
	double I1 = 1;
	double I2 = 1;
	for (int i = 0; i< dim; i++)
	{
		double W1 = Z1[contatore][i];
		double W2 = rho_diffusion * W1 + sqrt(1-rho_diffusion*rho_diffusion) * Z2[contatore][i];
		double jumpComponent1 = (J1 - 1) * X1[contatore][i];
		double jumpComponent2 = (J2 - 1) * X2[contatore][i];
		I1 = I1 * (1 + mu1 * dt + sigma1 * sqrt(dt) * W1 + jumpComponent1);
		I2 = I2 * (1 + mu2 * dt + sigma2 * sqrt(dt) * W2 + jumpComponent2);
	}
	double nuovoIndice = I1 * w1 + I2 * w2;
	return nuovoIndice;
}
