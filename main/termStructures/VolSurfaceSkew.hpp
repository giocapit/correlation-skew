#ifndef VolSurfaceSkew_hpp
#define VolSurfaceSkew_hpp
#include "VolSurface.hpp"
#include <vector>

using namespace std;
class VolSurfaceSkew: public VolSurface
{
	private:
		vector<double> strikes;
		vector<double> vol;
		int dim;

	public:
		VolSurfaceSkew(vector<double> strikes_, vector<double> vol_);
		~VolSurfaceSkew(){};


		double getVolatilityForStrike(double K);
		double getVolatility(int i) const;
		vector<double>* getStrikes();
		vector<double>* getVols();
		void setVol(double vol_, int i);
		int getDim();

};
#endif
