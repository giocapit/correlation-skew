#ifndef CorrelationSurface_hpp
#define CorrelationSurface_hpp


class CorrelationSurface
{
	private:
	public:
			CorrelationSurface(){};
			virtual ~CorrelationSurface(){};

			virtual double getCorr(int i)const=0;
};
#endif
