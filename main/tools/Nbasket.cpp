#include "Nbasket.hpp"

Nbasket::Nbasket(vector<Equity> components,
		vector<double> w)
{
	this->components = components;
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
