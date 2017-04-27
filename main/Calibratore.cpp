#include "Calibratore.hpp"
#include "mertonFormula.hpp"
#include "calculateCorrelationSkew.hpp"
#include "randomGenerator.hpp"
#include <gsl/gsl_vector.h>
#include <gsl/gsl_multifit_nlin.h>
#include <gsl/gsl_multifit_nlinear.h>
#include <gsl/gsl_blas.h>
#ifdef STAMPA_CALIBRAZIONE
#include <fstream>
#endif

int funzionaleCorrelationSkew2(const gsl_vector *x, void *data, gsl_vector *f)
{

  	size_t n = ((struct calibDataCorrelationSkew2 *)data)->n;
	std::vector<double> y = ((struct calibDataCorrelationSkew2 *)data)->y;
	std::vector<double> strikes = ((struct calibDataCorrelationSkew2 *)data)->K;
	double multiplier = ((struct calibDataCorrelationSkew2 *)data)->multiplier;
	double T = ((struct calibDataCorrelationSkew2 *)data)->T;
	double riskFree = ((struct calibDataCorrelationSkew2 *)data)->riskFree;
	double lambda1 = ((struct calibDataCorrelationSkew2 *)data)->lambda1;
	double J1 = ((struct calibDataCorrelationSkew2 *)data)->J1;
	double sigma1 = ((struct calibDataCorrelationSkew2 *)data)->sigma1;
	double lambda2 = ((struct calibDataCorrelationSkew2 *)data)->lambda2;
	double J2 = ((struct calibDataCorrelationSkew2 *)data)->J2;
	double sigma2 = ((struct calibDataCorrelationSkew2 *)data)->sigma2;
	double w1 = ((struct calibDataCorrelationSkew2 *)data)->w1;
	double w2 = ((struct calibDataCorrelationSkew2 *)data)->w2;
	int Nsim = 500000;
	int dim = 80;

	generator.seed();


	double rho_diffusion = gsl_vector_get (x, 0);
	double rho_jumps = gsl_vector_get (x, 1);
	int num_strikes = (int) n;
	std::vector<double> results(num_strikes,0);
	size_t i;

	calculateCorrelationSkewJumpDiffusionWithCorrelatedJumps(	multiplier,
														riskFree,
														lambda1 ,
														J1 ,
														sigma1 ,
														lambda2 ,
														J2 ,
														sigma2 ,
														rho_diffusion ,
														rho_jumps ,
														w1 ,
														w2 ,
														T ,
														num_strikes,
														strikes ,
														results,
														Nsim,
														dim
													);

#ifdef STAMPA_CALIBRAZIONE
	std::ofstream miofile;
	miofile.open("C:\\Users\\Giovanni\\Dropbox\\mip\\project_work\\Dati_e_eseguibili\\iterazioni_calibrazione.csv",std::ios_base::app);
	miofile << rho_diffusion << ";" << rho_jumps <<std::endl ;
	miofile.flush();
	miofile.close();
#endif


	for (i = 0;i<n;i++)
	{
		gsl_vector_set(f, i, results[i] - y[i]);
	}
	return GSL_SUCCESS;
}

std::vector<double> calibraCorrelationSkew2(std::vector<double> initParams,
		std::vector<double>& y,
		std::vector<double>& K,
		double multiplier,
		double horiz,
		double riskFree,
		double lambda1,
		double J1,
		double sigma1,
		double lambda2,
		double J2,
		double sigma2,
		double w1,
		double w2)
{

  	const gsl_multifit_nlinear_type *T = gsl_multifit_nlinear_trust;
	gsl_multifit_nlinear_parameters fdf_params = gsl_multifit_nlinear_default_parameters();
  	gsl_multifit_nlinear_workspace *w;
  	int status, info;
  	const size_t n = y.size();
  	const size_t p = initParams.size();
	struct calibDataCorrelationSkew2 d = { n, y, K, multiplier,	horiz, riskFree, lambda1, J1, sigma1, lambda2, J2, sigma2, w1, w2};
	fdf_params.h_df = 1e-4;
	//allocate workspace
  	w = gsl_multifit_nlinear_alloc (T, &fdf_params, n, p);

	gsl_multifit_nlinear_fdf f;

	const double xtol = 1e-16;
  	const double gtol = 1e-24;
  	const double ftol = 0.0;

	f.f = &funzionaleCorrelationSkew2;
	f.df = NULL;
	f.n = n;
	f.p = p;
	f.params = &d;
	double *x = &initParams[0];
	gsl_vector_view x_init = gsl_vector_view_array(x,p);

	gsl_multifit_nlinear_init(&x_init.vector, &f, w);

  	/* compute initial residual norm */
	gsl_vector *res_f; double chi,chi0;
 	res_f = gsl_multifit_nlinear_residual(w);
  	chi0 = gsl_blas_dnrm2(res_f);

	//risoluzione delsistema
	status = gsl_multifit_nlinear_driver(20, xtol, gtol, ftol, NULL, NULL,  &info, w);
	std::vector<double> calib_output(2);
	for (size_t j=0; j<p; j++)
	{
		calib_output[j] = gsl_vector_get(w->x, j);
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
	return calib_output;
}
