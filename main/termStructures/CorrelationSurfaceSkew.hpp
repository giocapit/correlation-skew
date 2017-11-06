#ifndef correlation_surface_skew_hpp
#define correlation_Surface_skew_hpp
#include "CorrelationSurface.hpp"
#include <vector>

using namespace std;

class CorrelationSurfaceSkew: public CorrelationSurface
{
	private:
			vector<double> strikes;
			vector<double> correlations;
			int dim;
	public:
			CorrelationSurfaceSkew(vector<double> strikes, vector<double> correlations);
			~CorrelationSurfaceSkew(){};
			int getDim();
			//vector<double> getStrikes();

			vector<double>* getStrikes();
			vector<double>* getCorrs();


			double getCorr(int i) const;

			void setCorrelation(double corr, int i);
};

#endif
