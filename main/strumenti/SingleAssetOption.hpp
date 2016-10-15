#include "Option.hpp"
#include "Equity.hpp"

class SingleAssetOption: public Option
{
	private:
		Equity *stock;
	public:
		SingleAssetOption(double strike_,Equity *asset_,double expiry_);
		~SingleAssetOption(){};
		double payoff(double price) const {return 0;}
};
