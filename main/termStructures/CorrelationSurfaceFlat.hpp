#include "CorrelationSurface.hpp"

class CorrelationSurfaceFlat : public CorrelationSurface
{
	private:
		double corr;
	public:
		CorrelationSurfaceFlat(double corr_);
		~CorrelationSurfaceFlat();

		double getCorr();
};
