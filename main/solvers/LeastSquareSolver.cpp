#include "LeastSquareSolver.hpp"
#include <gsl/gsl_vector.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_multifit_nlin.h>
#include <gsl/gsl_multifit_nlinear.h>
#include <gsl/gsl_blas.h>


struct leastSquaresParams
{
	MultiFunctional* fun;
	size_t n;
	size_t p;
};


int leastSquaresFunctional (const gsl_vector * x, void *params,
		gsl_vector * f)
{
	size_t n = ((struct leastSquaresParams *)params)->n;
	size_t p = ((struct leastSquaresParams *)params)->p;
	std::vector<double> v = std::vector<double>(n,0);
	for (size_t i = 0; i < p; i++)
	{
		v[i] = gsl_vector_get (x, i);
	}

	MultiFunctional* fun = ((struct leastSquaresParams *) params)->fun;

	const std::vector<double> y = (*fun)(v);

	for (size_t i=0; i<n; i++){
		gsl_vector_set (f, i, y[i]);
	}
	return GSL_SUCCESS;
}

void print_nls_status (const size_t iter, void * params, const gsl_multifit_nlinear_workspace* w)
{

	printf ("iter = %3u x = % .8f % .8f % .8f "
			"f(x) = % .5e % .5e % .5e % .5e % .5e\n",
			iter,
			gsl_vector_get (w->x, 0),
			gsl_vector_get (w->x, 1),
			gsl_vector_get (w->x, 2),
			gsl_vector_get (w->f, 0),
			gsl_vector_get (w->f, 1),
			gsl_vector_get (w->f, 2),
			gsl_vector_get (w->f, 3),
			gsl_vector_get (w->f, 4)
			);

	for (int i=0; i<4; i++)
	{
	gsl_vector_view v = gsl_matrix_row(w->J,i);
	printf(" % .12e  % .12e % .12e\n", 
			gsl_vector_get (&v.vector, 0),
			gsl_vector_get (&v.vector, 1),
			gsl_vector_get (&v.vector, 2)
	      );

	}
	
	printf ("gradient = % .5e % .5e % .5e \n",
			gsl_vector_get (w->g, 0),
			gsl_vector_get (w->g, 1),
			gsl_vector_get (w->g, 2)
			);
}

LeastSquaresSolver::LeastSquaresSolver(MultiFunctional * f, std::vector<double> x_init)
{
	this->fun = f;
	this->x_init = x_init;
	p = x_init.size();
	n = fun->getDimY();
	sol = std::vector<double>(p,0);

};

std::vector<double> LeastSquaresSolver:: getSol()
{
	return sol;

}

int LeastSquaresSolver::solve(void)
{

  	const gsl_multifit_nlinear_type *T = gsl_multifit_nlinear_trust;
	gsl_multifit_nlinear_parameters fdf_params = gsl_multifit_nlinear_default_parameters();
  	gsl_multifit_nlinear_workspace *w;
  	int status, info, iter = 0;
	struct leastSquaresParams pars = {fun,n,p};
	fdf_params.h_df = 1e-4;
	//allocate workspace
  	w = gsl_multifit_nlinear_alloc (T, &fdf_params, n, p);

	gsl_multifit_nlinear_fdf f;

	const double xtol = 1e-16;
  	const double gtol = 1e-16;
  	const double ftol = 0.0;

	f.f = &leastSquaresFunctional;
	f.df = NULL;
	f.n = n;
	f.p = p;
	f.params = &pars;

	gsl_vector *x = gsl_vector_alloc (p);
	
	for (int i = 0; i<p; i++)
	{
		gsl_vector_set (x, i, x_init[i]);
	}
	
	gsl_multifit_nlinear_init(x, &f, w);

  	/* compute initial residual norm */
	gsl_vector *res_f; double chi,chi0;
 	res_f = gsl_multifit_nlinear_residual(w);
  	chi0 = gsl_blas_dnrm2(res_f);

	print_nls_status (iter,&pars, w);
	//risoluzione delsistema
	//status = gsl_multifit_nlinear_driver(200, xtol, gtol, ftol, &print_nls_status, NULL,  &info, w);
	do
	{
		iter++;

		status = gsl_multifit_nlinear_iterate (w);

		print_nls_status (iter,&pars, w);

		if (status)
		{
			printf("unexpected exit from iteration\n");
			break;
		}

		status = gsl_multifit_nlinear_test (xtol, gtol, ftol, &info, w);
	}
	while (status == GSL_CONTINUE && iter < 1000);
	
	for (size_t j=0; j<p; j++)
	{
		sol[j] = gsl_vector_get(w->x, j);
	}
  /* compute final residual norm */
  	chi = gsl_blas_dnrm2(res_f);

//#define FIT(i) gsl_vector_get(s->x, i)
#define ERR(i) sqrt(gsl_matrix_get(covar,i,i))

  fprintf(stderr, "summary from method '%s'\n",
          gsl_multifit_nlinear_name(w));
  fprintf(stderr, "number of iterations: %zu\n",
          gsl_multifit_nlinear_niter(w));
  fprintf(stderr, "function evaluations: %zu\n", f.nevalf);
  fprintf(stderr, "Jacobian evaluations: %zu\n", f.nevaldf);
  fprintf(stderr, "reason for stopping: %s\n",
          (info == 1) ? "small step size" : "small gradient");
  fprintf(stderr, "initial |f(x)| = %g\n", chi0);
  fprintf(stderr, "final   |f(x)| = %g\n", chi);

  {
    double dof = n - p;
    double c = GSL_MAX_DBL(1, chi / sqrt(dof));

    fprintf(stderr, "chisq/dof = %g\n",  pow(chi, 2.0) / dof);

  }

  fprintf (stderr, "status = %s\n", gsl_strerror (status));

  gsl_multifit_nlinear_free (w);
	return 0;
}
