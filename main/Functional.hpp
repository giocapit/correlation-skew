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
	protected:
		size_t dim_y;
 		size_t dim_x;   
	public:
		MultiFunctional(int dim_x, int dim_y)
		{
			this->dim_x = (size_t)dim_x;
			this->dim_y = (size_t)dim_y;
		};

		MultiFunctional(){};
		virtual ~MultiFunctional(){};
		size_t getDimY() const { return dim_y; }

		virtual std::vector<double> operator()(const std::vector<double> & x) const = 0;//{return 0;}

};

#endif
