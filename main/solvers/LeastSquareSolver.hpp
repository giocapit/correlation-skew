#ifndef LeastSquaresSolver_hpp
#define LeastSquaresSolver_hpp
#include "Functional.hpp"
#include <vector>
#include <gsl/gsl_vector.h>
#include <gsl/gsl_multiroots.h>

class LeastSquaresSolver{

	private:
		MultiFunctional *fun;
		std::vector<double> x_init;
		std::vector<double> sol;
		size_t n;
		size_t p;
	//	int print_state (size_t iter, gsl_multiroot_fsolver * s);

	public:
		LeastSquaresSolver(MultiFunctional * f, std::vector<double> x_init);


		~LeastSquaresSolver(){};

		std::vector<double> getSol();


		int solve (void);
};

#endif
