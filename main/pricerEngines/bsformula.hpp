#ifndef bs_formula_hpp
#define  bs_formula_hpp
double blackD1(double S0,
		double K,
		double r,
		double T,
		double sigma,
		double q);

double blackD2(double S0,
		double K,
		double r,
		double T,
		double sigma,
		double q);

double bsprice(double S0,
		double K,
		double r,
		double T,
		double sigma,
		double q,
		int cp);

#endif
