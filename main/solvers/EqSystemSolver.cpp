#include "EqSystemSolver.hpp"
#include <stdlib.h>
#include <stdio.h>

struct rparams
{
	MultiFunctional* fun;
	MultiFunctional* dfun;
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

int call_df (const gsl_vector * x, void *params,
		gsl_matrix * J)
{
	const std::vector<double> v = {
		gsl_vector_get (x, 0),
		gsl_vector_get (x, 1),
		gsl_vector_get (x, 2),
	};

	MultiFunctional* dfun = ((struct rparams *) params)->dfun;

	const std::vector<double> y = (*dfun)(v);


	gsl_matrix_set (J, 0, 0, y[0]);
	gsl_matrix_set (J, 0, 1, y[1]);
	gsl_matrix_set (J, 0, 2, y[2]);
	gsl_matrix_set (J, 1, 0, y[3]);
	gsl_matrix_set (J, 1, 1, y[4]);
	gsl_matrix_set (J, 1, 2, y[5]);
	gsl_matrix_set (J, 2, 0, y[6]);
	gsl_matrix_set (J, 2, 1, y[7]);
	gsl_matrix_set (J, 2, 2, y[8]);

	return GSL_SUCCESS;
}

int call_fdf (const gsl_vector * x, void *params,
		gsl_vector * f, gsl_matrix * J)
{
	call_f(x, params, f);
	call_df(x, params, J);

	return GSL_SUCCESS;
};


	int
EqSystemSolver::print_state (size_t iter, gsl_multiroot_fsolver * s)
{
	printf ("iter = %3u x = % .5e % .5e % .5e"
			"f(x) = % .3e % .3e % .3e\n",
			iter,
			gsl_vector_get (s->x, 0),
			gsl_vector_get (s->x, 1),
			gsl_vector_get (s->x, 2),
			gsl_vector_get (s->f, 0),
			gsl_vector_get (s->f, 1),
			gsl_vector_get (s->f, 2));
	return 0;
}

	int
EqSystemSolver::print_state_df (size_t iter, gsl_multiroot_fdfsolver * s)
{
	printf ("iter = %3u x = % .5f % .5f % .5f"
			"f(x) = % .3e % .3e % .3e\n",
			iter,
			gsl_vector_get (s->x, 0),
			gsl_vector_get (s->x, 1),
			gsl_vector_get (s->x, 2),
			gsl_vector_get (s->f, 0),
			gsl_vector_get (s->f, 1),
			gsl_vector_get (s->f, 2));
	printf("residue = % .3f\n",
			abs(gsl_vector_get (s->f, 0))+
			abs(gsl_vector_get (s->f, 1))+
			abs(gsl_vector_get (s->f, 2)));
	return 0;
}

EqSystemSolver::EqSystemSolver(MultiFunctional * f, std::vector<double> x_init)
{
	this->fun = f;
	this->x_init = x_init;
	sol = std::vector<double>(3,0);

};

EqSystemSolver::EqSystemSolver(MultiFunctional * f, MultiFunctional * df, std::vector<double> x_init)
{
	this->fun = f;
	this->dfun = df;
	this->x_init = x_init;
	sol = std::vector<double>(3,0);

};

std::vector<double> EqSystemSolver:: getSol()
{
	return sol;

}


int EqSystemSolver::solve (void)
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
			gsl_multiroot_test_residual (s->f, 1e-12);
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
};



int EqSystemSolver::solveWithDf (void)
{
	const gsl_multiroot_fdfsolver_type *T;
	gsl_multiroot_fdfsolver *s;

	int status;
	size_t i, iter = 0;

	const size_t n = 3;
	struct rparams p = {fun, dfun};
	gsl_multiroot_function_fdf f = {&call_f,
		&call_df,
		&call_fdf,
		n, &p};

	gsl_vector *x = gsl_vector_alloc (n);

	for (i = 0; i<n; i++)
	{
		gsl_vector_set (x, i, x_init[i]);
	}

	T = gsl_multiroot_fdfsolver_hybridsj;
	s = gsl_multiroot_fdfsolver_alloc (T, n);
	gsl_multiroot_fdfsolver_set (s, &f, x);

	print_state_df (iter, s);

	do
	{
		iter++;

		status = gsl_multiroot_fdfsolver_iterate (s);

		print_state_df (iter, s);

		if (status)
			break;

		status = gsl_multiroot_test_residual (s->f, 1e-7);
	}
	while (status == GSL_CONTINUE && iter < 1000);

	printf ("status = %s\n", gsl_strerror (status));

	for (int i=0; i < n; i++)
	{
		sol[i]=gsl_vector_get(s->x,i);
	}

	gsl_multiroot_fdfsolver_free (s);
	gsl_vector_free (x);
	return 0;
}

