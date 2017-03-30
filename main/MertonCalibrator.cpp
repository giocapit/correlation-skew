#include "MertonCalibrator.hpp"
#include "mertonFormula.hpp"
#include "randomGenerator.hpp"
#include <gsl/gsl_vector.h>
#include <gsl/gsl_multifit_nlin.h>
#include <gsl/gsl_multifit_nlinear.h>
#include <gsl/gsl_blas.h>
#ifdef STAMPA_CALIBRAZIONE
#include <fstream>
#endif

int funzionaleMerton(const gsl_vector *x, void *data, gsl_vector *f)
{
	
  	size_t n = ((struct calibData *)data)->n;
	std::vector<double> y = ((struct calibData *)data)->y;
	std::vector<double> K = ((struct calibData *)data)->K;
	double S0 = ((struct calibData *)data)->S0;
	double T = ((struct calibData *)data)->T;
	double r = ((struct calibData *)data)->r;



	double lambda = gsl_vector_get (x, 0);
	double J = gsl_vector_get (x, 1);
	double sigma = gsl_vector_get (x, 2);

	size_t i;

#ifdef STAMPA_CALIBRAZIONE
	std::ofstream miofile;
	miofile.open("C:\\Users\\Giovanni\\Dropbox\\mip\\project_work\\Dati_e_eseguibili\\iterazioni_calibrazione.csv",std::ios_base::app);
	miofile << lambda << ";" << J << ";" << sigma <<std::endl ;
	miofile.flush();
	miofile.close();
#endif


	for (i = 0;i<n;i++)
	{
		double Yi = mertonPrice(S0,K[i]*S0,r,T,lambda,J,sigma,1);
		gsl_vector_set(f, i, Yi - y[i]);
	}
	return GSL_SUCCESS;
}

std::vector<double> calibraMerton(std::vector<double> initParams, 
		std::vector<double>& y, 
		std::vector<double>& K, 
		double S0,
		double horiz,
		double r)
{

  	const gsl_multifit_fdfsolver_type *T = gsl_multifit_fdfsolver_lmsder;
  	gsl_multifit_fdfsolver *s;
  	int status, info;
  	const size_t n = y.size();
  	const size_t p = initParams.size();
	struct calibData d = { n, y, K, S0,horiz, r };

  	s = gsl_multifit_fdfsolver_alloc (T, n, p);

	gsl_multifit_function_fdf f;
	
	const double xtol = 1e-8;
  	const double gtol = 1e-8;
  	const double ftol = 0.0;

	f.f = &funzionaleMerton;
	f.df = NULL;
	f.n = n;
	f.p = p;
	f.params = &d;
	double *x = &initParams[0];
	gsl_vector_view x_init = gsl_vector_view_array(x,p);

	gsl_multifit_fdfsolver_set(s, &f, &x_init.vector);

  	/* compute initial residual norm */
	gsl_vector *res_f; double chi,chi0;
 	 res_f = gsl_multifit_fdfsolver_residual(s);
  	chi0 = gsl_blas_dnrm2(res_f);

	//risoluzione delsistema
	status = gsl_multifit_fdfsolver_driver(s, 20, xtol, gtol, ftol, &info);
	std::vector<double> calib_output(3);
	for (size_t j=0; j<p; j++)
	{
		calib_output[j] = gsl_vector_get(s->x, j);
	}
  /* compute final residual norm */
  	chi = gsl_blas_dnrm2(res_f);

//#define FIT(i) gsl_vector_get(s->x, i)
#define ERR(i) sqrt(gsl_matrix_get(covar,i,i))

  fprintf(stderr, "summary from method '%s'\n",
          gsl_multifit_fdfsolver_name(s));
  fprintf(stderr, "number of iterations: %zu\n",
          gsl_multifit_fdfsolver_niter(s));
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

  gsl_multifit_fdfsolver_free (s);
	return calib_output;
}
