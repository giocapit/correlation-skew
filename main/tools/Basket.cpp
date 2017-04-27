#include "Basket.hpp"
#include "BasketOption.hpp"
#include "Functional.hpp"
#include "VolSurfaceSkew.hpp"
#include "CorrelationExtractors.hpp"
#include <fstream>

using namespace std;

int MCOptionPricer::N = 0;


Basket::~Basket()
{
	delete corrSurf;
}

void Basket::initializeCorrelationSurface()
{
	//assumo che il vettore degli strike su cui sono calcolati gli skew di volatilità dei componenti coincidano
	vector<double> *strikesTmp = ((VolSurfaceSkew*)(component1->getImplVolSurface()))->getStrikes();
	vector<double> strikes(*strikesTmp);
	vector<double> corrs(strikes.size(),0.0);
	corrSurf = new CorrelationSurfaceSkew(strikes,corrs);

}

void Basket::calculateCorrelationSurface(ProcessBiVariate* p, double T, double riskFreeRate)
{
	calculateCorrelationSurface( p,  T,  riskFreeRate, 1000000);
}

void Basket::calculateCorrelationSurface(ProcessBiVariate* p, double T, double riskFreeRate,int Nsim_)
{
	//1.calibro i parametri lambda, J, sigma sullo skew d volatilitÃ  per entrambi i componenti del basket
	//2.calcolo il prezzo della call sul basket per ciascuno degli strike con la dinamica a salti
	//3.per ogni valore dello strike trovo il parametro rho_BS che riproduce il prezzo della call sotto la dinamica log normale
	initializeCorrelationSurface();	
	CorrelationSurfaceSkew * corrSurfSkew = (CorrelationSurfaceSkew*) corrSurf;
	//inizializzo un vettore di opzioni. Un opzione per ciascuno strike.
	int Nsim = Nsim_;
	int dimSkew = corrSurfSkew->getDim();
	vector<double>* strikes = corrSurfSkew->getStrikes();
	BasketOption *basketOptions = new BasketOption[dimSkew];
	MCOptionPricer *pricers = new MCOptionPricer[dimSkew];
	for (int i = 0; i < dimSkew; i++)
	{
		basketOptions[i] = BasketOption(T, this, (*strikes)[i], BasketOption::call);
		MCOptionPricer *pricerPointer = new MCOptionPricer(&basketOptions[i], p, riskFreeRate, Nsim);
		pricers[i] = *pricerPointer;
	}

	for (int j = 0; j < Nsim; j++)
	{
		p->generaCammino(T);
		double prezzoJesimo = p->getAssetEvaluation(this,riskFreeRate,T);
		for (int i = 0; i < dimSkew; i++)
		{
			pricers[i].updateCumulatedPayoff(prezzoJesimo);
		}
		p->increaseContatore();

	}

	double *optionPrices = new double[dimSkew];

	SimpleCorrelationExtractor corrExtractor = SimpleCorrelationExtractor(this, p);

#ifdef STAMPA_PREZZI_BASKET
	ofstream miofile;
	miofile.open("C:\\Users\\Giovanni\\Dropbox\\mip\\project_work\\Dati_e_eseguibili\\dump.csv");
#endif

	for (int i = 0; i < dimSkew; i++)
	{
		double sigmaBSComponent1 = component1->getImpliedVolatility(i);
		double sigmaBSComponent2 = component2->getImpliedVolatility(i);
		optionPrices[i] = pricers[i].getOptionPriceFromCumulatedPayoff();
#ifdef STAMPA_PREZZI_BASKET
		miofile << optionPrices[i] << std::endl ;
		miofile.flush();
#endif
		double rho = corrExtractor.extract(sigmaBSComponent1,sigmaBSComponent2, optionPrices[i], (*strikes)[i], riskFreeRate, T);

		((CorrelationSurfaceSkew*) corrSurf)->setCorrelation(rho,i);
	}
#ifdef STAMPA_PREZZI_BASKET
	miofile.close();
#endif
	delete [] basketOptions;
	delete [] pricers;
	delete [] optionPrices;
}

CorrelationSurface* Basket::getImplCorrSurface() const
{
	return corrSurf;
}
