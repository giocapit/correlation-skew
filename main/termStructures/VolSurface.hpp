#ifndef VolSurface_hpp
#define VolSurface_hpp

class VolSurface
{
	private:

	public:
		VolSurface(){};
		virtual ~VolSurface(){};

		virtual double getVolatilityForStrike(double K)= 0;
		virtual double getVolatility(int i) const = 0;
};
#endif
