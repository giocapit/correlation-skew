#ifndef functional_hpp
#define functional_hpp
class  Functional
{
	public:
		Functional(){};
		virtual ~Functional(){};

		virtual double operator()(double x) const = 0;//{return 0;}

};
#endif
