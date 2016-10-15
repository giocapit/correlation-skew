#ifndef Option_hpp
#define Option_hpp
#include "Asset.hpp"

class Option
{
	public:
		enum type {call = 1,put = -1};
		Option(){};
		Option(double expiry_, Asset * underlying_, double strike_, type cp_)
		{
			expiry = expiry_;
			underlying = underlying_;
			strike = strike_;
			cp = cp_;
		};
		~Option(){};
		
		double getStrike() const;
		double getExpiry() const;
		virtual double payoff(double S) const= 0;
		Asset* getUnderlying() const;
	protected:
		double strike;
		double expiry;
		Asset *underlying;
		type cp;
};

#endif
