#include "OptionPricer.hpp"
#include "MCResults.hpp"

class MCOptionPricer: public OptionPricer
{
	private:
		static int N;//numero di simulazioni
		MCResults* statistiche;
	public:
		MCOptionPricer():OptionPricer()
	{
		statistiche = 0;
	};
		MCOptionPricer(Option *opzione, 
				Process *processo,
				double riskFreeRate_)
			: OptionPricer(opzione, processo,riskFreeRate_)
	{
		statistiche = new MCResults(N);
	}
		MCOptionPricer(Option *opzione, 
				Process *processo,
				double riskFreeRate_,
				int N_)
			: OptionPricer(opzione, processo,riskFreeRate_)
	{
		N = N_;
		statistiche = new MCResults(N);
	}

		MCOptionPricer(Option *opzione,
				Process *processo,
				double riskFreeRate_,
				int N_,
				MCResults *statistiche_)
			: OptionPricer(opzione, processo,riskFreeRate_)
	{
		N = N_;
		statistiche = statistiche_;
	}


		~MCOptionPricer();

		double getOptionPrice();

		double getOptionPriceFromAlreadyGeneratedPath() const;

		void updateCumulatedPayoff(double underlyingPrice) const;

		double getOptionPriceFromCumulatedPayoff();
		double getOptionPriceWithGsl();

	double getErroreMontecarlo() const {
		return statistiche->getMontecarloError();
	}
};

