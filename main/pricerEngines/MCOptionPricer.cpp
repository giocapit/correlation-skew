#include "MCOptionPricer.hpp"
#include "MCResults.hpp"
#include <cmath>


MCOptionPricer::~MCOptionPricer()
{
	delete statistiche;
};

double MCOptionPricer::getOptionPrice()
{
	double prezzoIesimo;
	double mioPayoff;
	double T = opzione->getExpiry();
	for (int i = 0; i < N; i++)
	{
		processo->generaCammino(T);
		
		prezzoIesimo = processo->getAssetEvaluation(opzione->getUnderlying(), 
							riskFreeRate,
							T);
		processo->increaseContatore();
		mioPayoff = opzione->payoff(prezzoIesimo);
		statistiche	->addPayoff(mioPayoff);
	}

	double mediaPayoff = statistiche->getMeanPayoff();
	double price = mediaPayoff * exp(-riskFreeRate * T);

	return price;
}

double MCOptionPricer::getOptionPriceFromAlreadyGeneratedPath() const
{
	double prezzoIesimo;
	double mioPayoff;
	double payoffCumulato = 0;
	double T = opzione->getExpiry();
	processo->setContatore(0);
	for (int i = 0; i < N; i++)
	{

		prezzoIesimo = processo->getAssetEvaluation(opzione->getUnderlying(),
							riskFreeRate,
							T);
		processo->increaseContatore();

		mioPayoff = opzione->payoff(prezzoIesimo);
		payoffCumulato = payoffCumulato + mioPayoff;
	}

	double price = payoffCumulato/N * exp(-riskFreeRate * T);

	return price;
}

void MCOptionPricer::updateCumulatedPayoff(double underlyingPrice) const
{
	double mioPayoff;
	mioPayoff = opzione->payoff(underlyingPrice);
	statistiche->addPayoff(mioPayoff);
}

double MCOptionPricer::getOptionPriceFromCumulatedPayoff()
{
	double T = opzione->getExpiry();
	double meanPayoff = statistiche->getMeanPayoff();
	double price = meanPayoff * exp(-riskFreeRate * T);

	return price;

}

double MCOptionPricer::getOptionPriceWithGsl()
{
	double prezzoIesimo;
	double mioPayoff;
	double payoffCumulato = 0;
	double T = opzione->getExpiry();
	processo->generaCamminiOneShot(T,N);
	for (int i = 0; i < N; i++)
	{
		prezzoIesimo = processo->getAssetEvaluation(opzione->getUnderlying(), 
							riskFreeRate,
							T);
		processo->increaseContatore();
		mioPayoff = opzione->payoff(prezzoIesimo);
		payoffCumulato = payoffCumulato + mioPayoff;
	}

	double price = payoffCumulato/N * exp(-riskFreeRate * T);

	return price;
}
