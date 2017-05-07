#ifndef functional_hpp
#define functional_hpp
#include <vector>

class  Functional
{
	public:
		Functional(){};
		virtual ~Functional(){};

		virtual double operator()(double x) const = 0;//{return 0;}

};

class MultiFunctional
{
	public:
		MultiFunctional(){};
		virtual ~MultiFunctional(){};

		virtual std::vector<double> operator()(const std::vector<double> & x) const = 0;//{return 0;}

};
#endif
