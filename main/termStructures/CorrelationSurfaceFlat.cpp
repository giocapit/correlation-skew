#include "CorrelationSurfaceFlat.hpp"

CorrelationSurfaceFlat::CorrelationSurfaceFlat(double corr_)
{
	corr = corr_;
}

double CorrelationSurfaceFlat::getCorr()
{
	return corr;
}
