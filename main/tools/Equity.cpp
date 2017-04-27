#include "Equity.hpp"
#include "VolSurfaceSkew.hpp"
#include "mertonFormula.hpp"
#include "ProcessJumpDiffusion.hpp"
#include "bsImplVol.hpp"
#include <cstdio>
#ifdef STAMPA_VOL
#include <fstream>
#endif

Equity::Equity(double spot_)
{
	spot = spot_;
	dividendYield = 0;
	implVol = NULL;

		
}

Equity::Equity(double spot_, VolSurface *vol)
{
	spot = spot_;
	dividendYield = 0;
	implVol = vol;
		
}

Equity::~Equity()
{
	delete implVol;	
}

double Equity::getSpot()
{
	return spot;
}

double Equity::getDividendYield() const
{
	return dividendYield;
}

VolSurface* Equity::getImplVolSurface() const
{
	return implVol;
}

double Equity::getImpliedVolatility(int i) const
{
	return implVol->getVolatility(i);
}

void Equity::initializeVolatilitySurface(vector<double> strikes)
{
	//assumo che gli skew di volatilità dei componenti coincidano
	vector<double> vols(strikes.size(),0.0);
	implVol = new VolSurfaceSkew(strikes,vols);

}

void Equity::calculateVolatilitySurface(Process* process, double T,double riskFree)
{
	VolSurfaceSkew* implVolSkew = (VolSurfaceSkew*)implVol;
	int dimVol = implVolSkew->getDim();
	//inizializzo un vettore di opzioni. Un opzione per ciascuno strike.
	vector<double>* strikes = implVolSkew->getStrikes();
	//SingleAssetOption *equityOptions = new SingleAssetOption[dimVol];
	//cablo nel codice il fatto che il prezzo viene calcolato con la formula di Merton
	//in una futura evoluzione si proverà a rendere la funzione generica: a seconda del processo passato in input cambio la procedura per il pricing
	double lambda = ((ProcessJumpDiffusion*)process)->getLambda();
	double J = ((ProcessJumpDiffusion*)process)->getJ();
	double sigma = ((ProcessJumpDiffusion*)process)->getSigma();
	for (int i = 0; i < dimVol ; i++)
	{
		double optPrice = mertonPrice(spot,
		(*strikes)[i] * spot,
		riskFree,
		T,
		lambda,
		J,
		sigma,
		1);
		double vola = bsImplVol(spot, optPrice, (*strikes)[i] * spot, riskFree,T);
		implVolSkew->setVol(vola,i);
	}
#ifdef STAMPA_VOL
	ofstream miofile;
	miofile.open("C:\\Users\\Giovanni\\Dropbox\\mip\\project_work\\Dati_e_eseguibili\\vols.csv",std::ios_base::app);
	for (int i = 0; i < dimVol; i++)
	{
		miofile << implVolSkew->getVolatility(i) << "\n";
	}
	miofile.close();
#endif


}
