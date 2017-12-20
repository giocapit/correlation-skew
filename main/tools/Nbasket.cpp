#include "Nbasket.hpp"

Nbasket::Nbasket(vector<Equity> components,
		vector<double> w)
{
	this->components = components;
	this->weights = w;
	multiplier = 0;
	for (size_t i=0; i<components.size(); ++i)
	{
		multiplier += weights[i] * components[i].getSpot();
	}
};


Nbasket::Nbasket(double multiplier, vector<double> w)
{
	this->multiplier=multiplier;
	this->weights = w;
};

const double Nbasket::get_weight(int i) const
{
	return weights[i];
}

Equity* Nbasket::getComponent(int i)
{
	return &components[i];
}

const double Nbasket::getMultiplier()
{
	return multiplier;
}

const vector <double> * Nbasket::get_weights() const
{
	return & weights;
}
