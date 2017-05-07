#include "Functional.hpp"
#include <vector>
#include <stdlib.h>
#include <stdio.h>
#include <gsl/gsl_vector.h>
#include <gsl/gsl_multiroots.h>

		struct rparams
		{
			MultiFunctional* fun;
		};

		int call_f (const gsl_vector * x, void *params,
				gsl_vector * f)
		{
			const std::vector<double> v = {
				gsl_vector_get (x, 0),
				gsl_vector_get (x, 1),
				gsl_vector_get (x, 2),
			};

			MultiFunctional* fun = ((struct rparams *) params)->fun;

			const std::vector<double> y = (*fun)(v);


			gsl_vector_set (f, 0, y[0]);
			gsl_vector_set (f, 1, y[1]);
			gsl_vector_set (f, 2, y[2]);

			return GSL_SUCCESS;
		}

class EqSystemSolver{

	private:
		MultiFunctional *fun;
		std::vector<double> x_init;
		std::vector<double> sol;



		int
			print_state (size_t iter, gsl_multiroot_fsolver * s)
			{
				printf ("iter = %3u x = % .3f % .3f "
						"f(x) = % .3e % .3e\n",
						iter,
						gsl_vector_get (s->x, 0),
						gsl_vector_get (s->x, 1),
						gsl_vector_get (s->x, 2),
						gsl_vector_get (s->f, 0),
						gsl_vector_get (s->f, 1),
						gsl_vector_get (s->f, 2));
			}

	public:
		EqSystemSolver(MultiFunctional * f, std::vector<double> x_init)
		{
			this->fun = f;
			this->x_init = x_init;
			sol = std::vector<double>(3,0);

		}

		~EqSystemSolver(){};


		int solve (void)
		{
			const gsl_multiroot_fsolver_type *T;
			gsl_multiroot_fsolver *s;

			int status;
			size_t i, iter = 0;

			const size_t n = 3;
			struct rparams p = {fun};
			gsl_multiroot_function f = {&call_f, n, &p};

			gsl_vector *x = gsl_vector_alloc (n);

			for (i = 0; i<n; i++)
			{
				gsl_vector_set (x, i, x_init[i]);
			}

			T = gsl_multiroot_fsolver_hybrids;
			s = gsl_multiroot_fsolver_alloc (T, 3);
			gsl_multiroot_fsolver_set (s, &f, x);

			print_state (iter, s);

			do
			{
				iter++;
				status = gsl_multiroot_fsolver_iterate (s);

				print_state (iter, s);

				if (status)   /* check if solver is stuck */
					break;

				status =
					gsl_multiroot_test_residual (s->f, 1e-7);
			}
			while (status == GSL_CONTINUE && iter < 1000);

			printf ("status = %s\n", gsl_strerror (status));
			for (int i=0; i < n; i++)
			{
				sol[i]=gsl_vector_get(s->x,i);
			}

			gsl_multiroot_fsolver_free (s);
			gsl_vector_free (x);
			return 0;
		}
};

