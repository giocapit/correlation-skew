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
	double T = option->getExpiry();
	for (int i = 0; i < N; i++)
	{
		processo->generaCammino(T);
		
		prezzoIesimo = processo->getAssetEvaluation(option->getUnderlying(), 
							riskFreeRate,
							T);
		processo->increaseContatore();
		mioPayoff = option->payoff(prezzoIesimo);
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
	double T = option->getExpiry();
	processo->setContatore(0);
	for (int i = 0; i < N; i++)
	{

		prezzoIesimo = processo->getAssetEvaluation(option->getUnderlying(),
							riskFreeRate,
							T);
		processo->increaseContatore();

		mioPayoff = option->payoff(prezzoIesimo);
		payoffCumulato = payoffCumulato + mioPayoff;
	}

	double price = payoffCumulato/N * exp(-riskFreeRate * T);

	return price;
}

void MCOptionPricer::updateCumulatedPayoff(double underlyingPrice) const
{
	double mioPayoff;
	mioPayoff = option->payoff(underlyingPrice);
	statistiche->addPayoff(mioPayoff);
}

double MCOptionPricer::getOptionPriceFromCumulatedPayoff()
{
	double T = option->getExpiry();
	double meanPayoff = statistiche->getMeanPayoff();
	double price = meanPayoff * exp(-riskFreeRate * T);

	return price;

}

double MCOptionPricer::getOptionPriceWithGsl()
{
	double prezzoIesimo;
	double mioPayoff;
	double payoffCumulato = 0;
	double T = option->getExpiry();
	processo->generaCamminiOneShot(T,N);
	for (int i = 0; i < N; i++)
	{
		prezzoIesimo = processo->getAssetEvaluation(option->getUnderlying(), 
							riskFreeRate,
							T);
		processo->increaseContatore();
		mioPayoff = option->payoff(prezzoIesimo);
		payoffCumulato = payoffCumulato + mioPayoff;
	}

	double price = payoffCumulato/N * exp(-riskFreeRate * T);

	return price;
}
