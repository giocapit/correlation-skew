//#include <gsl/gsl_rng.h>
#include <vector>
//#include <gsl/gsl_randist.h>

class PoissonDistribution
{
	protected:
		double lambda;
		int (PoissonDistribution::*funcPointer)(double);
		class Extractor
		{
			public:
				Extractor(){};
				~Extractor(){};

				virtual int extract(double T, double lambda_);
		};
		
		class DegenerateExtractor:public Extractor
		{
			public:
				DegenerateExtractor(){};
				~DegenerateExtractor(){};
				int extract(double T, double lambda_);
		};

		Extractor* extractor;
//  const gsl_rng_type * Type;
//  gsl_rng * r;

	public:
		PoissonDistribution(double lambda_ = 0.0);
		~PoissonDistribution();

		int operator()(double T) ;
		int extractPoisson(double T);
		int extractPoissonNull(double T);

};


class PoissonDistributionAntitetica:public PoissonDistribution
{
	private:
		std::vector<double> estrazioniPassate;
		int dim;
		bool pari;
		int k;
	public:
		PoissonDistributionAntitetica(double lambda_ = 0.0,int dim_=0):PoissonDistribution(lambda_)
	{
			dim = dim_;
			estrazioniPassate = std::vector<double>(dim);
			pari = true;
			k = 0;
	}
		~PoissonDistributionAntitetica(){};

		double operator()(double T);

};
