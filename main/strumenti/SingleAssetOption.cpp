#include "SingleAssetOption.hpp"


SingleAssetOption::SingleAssetOption(double strike_, Equity *stock_, double expiry_)
{
	strike = strike_;
	stock = stock_;
	expiry = expiry_;
}
