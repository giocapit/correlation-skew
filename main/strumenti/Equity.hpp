#ifndef Equity_hpp
#define Equity_hpp

#include "VolSurface.hpp"
#include "Asset.hpp"
#include "Process.hpp"
#include <vector>

class Equity: public Asset
{
	private:
		double spot;
		double dividendYield;

		VolSurface *implVol;

	public:
		Equity(double spot_);
		Equity(double spot_, VolSurface *vol);
		~Equity();

		double getSpot();
		double getDividendYield() const;
		double getImpliedVolatility(int i) const;
		VolSurface* getImplVolSurface() const;
		void initializeVolatilitySurface(std::vector<double> strikes);
		void calculateVolatilitySurface(Process* process,double T, double riskFree);
};
#endif
