#include "Calibratore.hpp"
#include "mertonFormula.hpp"
#include <gsl/gsl_vector.h>
#include <gsl/gsl_multifit_nlin.h>


int func(const gsl_vector *x, void *data, gsl_vector *f)
{
	
  	size_t n = ((struct Calibratore::data *)data)->n;
	double *y = ((struct Calibratore::data *)data)->y;
	double *K = ((struct Calibratore::data *)data)->K;


	size_t i;

	for (i = 0;i<n;i++)
	{
		double Yi = g(x,K[i]);
		gsl_vector_set(f, i, Yi - y[i]);
	}
	return GSL_SUCCESS;
}

};

void Calibratore::calibra(vector<double> x, vector<double> y)
{

  	const gsl_multifit_fdfsolver_type *T = gsl_multifit_fdfsolver_lmsder;
  	gsl_multifit_fdfsolver *s;
  	int status, info;
  	const size_t n = y.size();
  	const size_t p = x.size();
	struct data d = { n, y };

  	s = gsl_multifit_fdfsolver_alloc (T, n, p);

	gsl_multifit_function_fdf f;
	
	const double xtol = 1e-8;
  	const double gtol = 1e-8;
  	const double ftol = 0.0;

	f.f = &func;
	f.df = NULL;
	f.n = n;
	f.p = p;
	f.params = &d;

	gsl_vector_view x_init = gsl_vector_view_array(x,p);

	gsl_multifit_fdfsolver_set(s, &f, &x_init.vector);

	status = gsl_multifit_fdfsolver_driver(s, 20, xtol, gtol, ftol, &info);
	double* calib_output;
	for (size_t j=0; j<p; j++)
	{
		calib_output[j] = gsl_vector_get(s->x, j);
	}
}

double Calibratore::g(gsl_vector x, double k)
{

	double lambda = gsl_vector_get (x, 0);
	double J = gsl_vector_get (x, 1);
	double sigma = gsl_vector_get (x, 2);
		

}



