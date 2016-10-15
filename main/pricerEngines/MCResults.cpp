#include "MCResults.hpp"
#include <cmath>
MCResults::MCResults(int payoffNumber_) {
	payoffNumber = payoffNumber_;
	payoffCumulato = 0;

}

MCResults::~MCResults() {}

void MCResults::addPayoff(double payoff)
{
	payoffCumulato = payoffCumulato + payoff;
}

double MCResults::getMeanPayoff() const
{
	return payoffCumulato/payoffNumber;
}

double MCResults::getMontecarloError() const
{
	return 0;
}

MCResultsErroreMontecarlo::MCResultsErroreMontecarlo(int payoffNumber_): MCResults(payoffNumber_)
{
	payoffQuadroCumulato = 0;
}

MCResultsErroreMontecarlo::~MCResultsErroreMontecarlo() {}

void MCResultsErroreMontecarlo::addPayoff(double payoff)
{
	MCResults::addPayoff(payoff);
	payoffQuadroCumulato = payoffQuadroCumulato + payoff * payoff;
}

double MCResultsErroreMontecarlo::getMontecarloError() const
{
	double meanPayoff = payoffCumulato/payoffNumber;
	double sigmaQuadro = payoffQuadroCumulato/payoffNumber - meanPayoff * meanPayoff;
	return sqrt(sigmaQuadro/ payoffNumber);
}

MCResultsErroreMontecarloAntitetico::MCResultsErroreMontecarloAntitetico(
		int payoffNumber_): MCResultsErroreMontecarlo(payoffNumber_)
{
	payoffCammino1 = 0;
	pari = true;
}

MCResultsErroreMontecarloAntitetico::~MCResultsErroreMontecarloAntitetico() {}

void MCResultsErroreMontecarloAntitetico::addPayoff(double payoff)
{
	MCResults::addPayoff(payoff);
	if (pari)
	{
		payoffCammino1 = payoff;
		pari = false;
	} else {
		payoffQuadroCumulato = payoffQuadroCumulato + std::pow((payoffCammino1 + payoff)/2,2);
		pari = true;
	}
}

double MCResultsErroreMontecarloAntitetico::getMontecarloError() const
{
	double meanPayoff = payoffCumulato/payoffNumber;
	double sigmaQuadro = payoffQuadroCumulato*2/payoffNumber - meanPayoff * meanPayoff;
	return sqrt(sigmaQuadro/ payoffNumber);
}
