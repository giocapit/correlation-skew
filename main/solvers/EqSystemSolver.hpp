#ifndef EqSystemSolver_hpp
#define EqSystemSolver_hpp
#include "Functional.hpp"
#include <vector>
#include <gsl/gsl_vector.h>
#include <gsl/gsl_multiroots.h>

class EqSystemSolver{

	private:
		MultiFunctional *fun;
		MultiFunctional *dfun;
		std::vector<double> x_init;
		std::vector<double> sol;



		int print_state (size_t iter, gsl_multiroot_fsolver * s);
		int print_state_df (size_t iter, gsl_multiroot_fdfsolver * s);

	public:
		EqSystemSolver(MultiFunctional * f, std::vector<double> x_init);

		EqSystemSolver(MultiFunctional * f, MultiFunctional * df, std::vector<double> x_init);

		~EqSystemSolver(){};

		std::vector<double> getSol();


		int solve (void);
		int solveWithDf (void);
};

#endif
