#include "VolSurfaceSkew.hpp"
#include <algorithm>
#include <vector>

VolSurfaceSkew::VolSurfaceSkew(vector<double> strikes_, vector<double> vols_)
{
	vol = vols_;
	strikes = strikes_;
	dim = strikes.size();
}
double VolSurfaceSkew::getVolatilityForStrike(double K)
{
	vector<double>::iterator i;
	i = std::find(strikes.begin(), strikes.end(), K);
	return *i;
}

double VolSurfaceSkew::getVolatility(int i) const
{
	return vol[i];
}

vector<double>* VolSurfaceSkew::getStrikes()
{
	return &strikes;
}

vector<double>* VolSurfaceSkew::getVols()
{
	return &vol;
}

void VolSurfaceSkew::setVol(double vol_, int i)
{
	vol[i] = vol_;
}

int VolSurfaceSkew::getDim()
{
	return dim;
}
