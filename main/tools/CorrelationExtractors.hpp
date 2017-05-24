#include "Functional.hpp"
#include "MCOptionPricer.hpp"
#include "ProcessBiVariateLognormal.hpp"
#include "ProcessBiVariateLognormalEulero.hpp"
#include "bsImplVol.hpp"
#include "froot.hpp"
#include "BasketOptionFormulaPricers.hpp"

class FunctionalForCorrelationSkewCalculation:public Functional
{
	private:
		ProcessBiVariateLognormalAbstract *p;
		MCOptionPricer *pricer;
		double price;
	public:
		FunctionalForCorrelationSkewCalculation(ProcessBiVariateLognormalAbstract * p_, MCOptionPricer *pricer_, double price_)
		{
			p = p_;
			pricer = pricer_;
			price = price_;
		}
		double operator()(double rho) const
		{
			p->setRho(rho);
			double priceBS = pricer->getOptionPriceFromAlreadyGeneratedPath();
#ifdef STAMPA_BISEZIONE
			ofstream miofile;
			miofile.open("C:\\Users\\Giovanni\\Dropbox\\mip\\project_work\\Dati_e_eseguibili\\dump.csv",std::ios_base::app);
			miofile << priceBS << ";" << rho <<std::endl ;
			miofile.flush();
			miofile.close();
#endif

			return priceBS-price;
		}

};

//la logica di questa classe può essere asorbita dentro a quella della classe precedente
//introducendo un wrapper del MCOptionPricer che reindirizza il getOptionPrice sul
//metodo getOptionPriecFromAlready...
class FunctionalForCorrelationSkewCalculationBis:public Functional
{
	private:
		ProcessBiVariateLognormalAbstract *p;
		OptionPricer *pricer;
		double price;
	public:
		FunctionalForCorrelationSkewCalculationBis(ProcessBiVariateLognormalAbstract * p_, OptionPricer *pricer_, double price_)
		{
			p = p_;
			pricer = pricer_;
			price = price_;
		}
		double operator()(double rho) const
		{
			p->setRho(rho);
			double priceBS = pricer->getOptionPrice();
#ifdef STAMPA_BISEZIONE
			ofstream miofile;
			miofile.open("C:\\Users\\Giovanni\\Dropbox\\mip\\project_work\\Dati_e_eseguibili\\dump.csv",std::ios_base::app);
			miofile << priceBS << ";" << rho <<std::endl ;
			miofile.flush();
			miofile.close();
#endif

			return priceBS-price;
		}

};
class CorrelationExtractor
{
	protected: 
		Basket* basket;

	public:
		CorrelationExtractor(Basket* basket)
		{
			this->basket = basket;
		}

		virtual ~CorrelationExtractor(){};

		virtual double extract(double sigmaBSComponent1, double sigmaBSComponent2,double optionPrice, double strike, double riskFreeRate, double T)=0;
};

class SimpleCorrelationExtractor: public CorrelationExtractor
{
	public:
		SimpleCorrelationExtractor(Basket* basket, ProcessBiVariate* p):CorrelationExtractor(basket){}

		double extract(double sigmaBSComponent1, double sigmaBSComponent2,double optionPrice, double strike, double riskFreeRate, double T);
};

class MCCorrelationExtractor: public CorrelationExtractor
{
	private:
		ProcessBiVariateLognormalAbstract *procBS;
	public:
		MCCorrelationExtractor(Basket *basket, ProcessBiVariate *p):CorrelationExtractor(basket)
		{

			bool usaEulero = p->useEulerToCalculateCorrelation();
			if (usaEulero)
			{
				procBS = new ProcessBiVariateLognormalEulero(p);
			}else{
				procBS = new ProcessBiVariateLognormal(p);
			}
		}

		~MCCorrelationExtractor()
		{
			procBS->prepareForDestruction();
			delete procBS;
		}

		double extract(double sigmaBSComponent1, double sigmaBSComponent2,double optionPrice, double strike, double riskFreeRate, double T);

};


class ThirdMomentCorrelationExtractor: public CorrelationExtractor
{
	private:
		ProcessBiVariateLognormalAbstract *procBS;
	public:
		ThirdMomentCorrelationExtractor(Basket* basket, ProcessBiVariate* p):CorrelationExtractor(basket)
	{
		procBS = new ProcessBiVariateLognormal(p);		
		}

		double extract(double sigmaBSComponent1, double sigmaBSComponent2,double optionPrice, double strike, double riskFreeRate, double T);
		~ThirdMomentCorrelationExtractor()
		{
			procBS->prepareForDestruction();
			delete procBS;
		}
};
