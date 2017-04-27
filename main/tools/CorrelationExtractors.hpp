#include "Functional.hpp"
#include "MCOptionPricer.hpp"
#include "ProcessBiVariateLognormal.hpp"
#include "ProcessBiVariateLognormalEulero.hpp"
#include "bsImplVol.hpp"
#include "froot.hpp"

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

class MCCorrelationExtractor
{
	private:
		Basket * basket;
		ProcessBiVariateLognormalAbstract *procBS;
	public:
		MCCorrelationExtractor(Basket *basket, ProcessBiVariate *p)
		{
			this->basket = basket;

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
