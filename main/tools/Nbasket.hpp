#ifndef Nbasket_hpp
#define Nbasket_hpp
#include "Equity.hpp"
#include "Asset.hpp"
#include "ProcessBiVariate.hpp"

class Nbasket:public Asset
{
	private:
		vector<Equity> components;
		vector<double> weights;

		double multiplier;


	public:
		Nbasket(vector<Equity> components,
				vector<double> w);

		Nbasket(double multiplier, vector<double> w);
		~Nbasket(){};

		const double get_weight(int i) const;

		const vector <double> * get_weights() const;

		Equity* getComponent(int i);

		const double getMultiplier();
		
};
#endif
