#include "VolSurface.hpp"

class VolSurfaceFlat: public VolSurface
{
	private:
		double vol;

	public:
		VolSurfaceFlat();
		~VolSurfaceFlat();

		double getVolatilityForStrike(double K);
};
