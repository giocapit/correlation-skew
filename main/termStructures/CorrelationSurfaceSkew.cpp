#include "CorrelationSurfaceSkew.hpp"


using namespace std;

CorrelationSurfaceSkew::CorrelationSurfaceSkew(vector<double> strikes_, vector<double> correlations_)
{
	strikes = strikes_;
	correlations = correlations_;
	dim = strikes.size();

}

int CorrelationSurfaceSkew::getDim()
{
	return dim;
}

vector<double>* CorrelationSurfaceSkew::getStrikes()
{
	return &strikes;
}

double CorrelationSurfaceSkew::getCorr(int i) const
{
	return correlations[i];
}

void CorrelationSurfaceSkew::setCorrelation(double corr, int i)
{
	correlations[i] = corr;
}

vector<double>* CorrelationSurfaceSkew::getCorrs()
{
	return &correlations;
}
