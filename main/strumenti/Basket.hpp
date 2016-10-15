#ifndef Basket_hpp
#define Basket_hpp
#include "Equity.hpp"
#include "CorrelationSurfaceSkew.hpp"
#include "Asset.hpp"
#include "ProcessBiVariate.hpp"

class Basket:public Asset
{
	private:
		Equity *component1;
		Equity *component2;
		double w1;
		double w2;

		double spot;
		double index;
		double multiplier;
		CorrelationSurface *corrSurf;


	public:
		Basket(Equity *component1_,
				Equity *component2_,
				double w1_,
				double w2_)
		{
			component1 = component1_;
			component2 = component2_;
			w1 = w1_;
			w2 = w2_;
			multiplier = component1->getSpot() * w1 + component2->getSpot() * w2;
			corrSurf = NULL;
		};

		Basket(double multiplier_,
				double w1_,
				double w2_,
				CorrelationSurface* corrSurf_)
		{
			component1 = NULL;
			component2 = NULL;
			multiplier = multiplier_;
			w1 = w1_;
			w2 = w2_;
			corrSurf = corrSurf_;
		};

		~Basket();

		void initializeCorrelationSurface();

		double get_w1()
		{
			return w1;
		}
		double get_w2()
		{
			return w2;
		}

		Equity* getComponent1()
		{
			return component1;
		}

		Equity* getComponent2()
		{
			return component2;
		}

		double getImpliedCorrelation(int i)
		{
			return ((CorrelationSurfaceSkew*)corrSurf)->getCorr(i);
		}

		CorrelationSurface* getImplCorrSurface() const;

		double getMultiplier()
		{
			return multiplier;
		}
		
		void calculateCorrelationSurface(ProcessBiVariate *p, double T, double riskFreeRate, int Nsim_);

		void calculateCorrelationSurface(ProcessBiVariate *p, double T, double riskFreeRate);
};
#endif
