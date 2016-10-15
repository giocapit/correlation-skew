#include <vector>

class BiVariateJumpDistribution
{
	protected:
		double lambda1;
		double lambda2;
		double rho;
		double P00;
		double P10;
		double P01;
		double P11;
//  const gsl_rng_type * Type;
//  gsl_rng * r;

	public:
		BiVariateJumpDistribution(double lambda1_ = 0.0,double lambda2_ = 0.0,double rho_ = 0.0);
		virtual ~BiVariateJumpDistribution();

		virtual int operator()(int& x1, int& x2);

};


class BiVariateJumpDistributionAntitetica:public BiVariateJumpDistribution
{
	private:
		std::vector<double> estrazioniPassate;
		int dim;
		bool pari;
		int k;
	public:
			BiVariateJumpDistributionAntitetica(double lambda1_ = 0.0,double lambda2_ = 0.0,double rho_ = 0.0,int dim_=0):BiVariateJumpDistribution(lambda1_,lambda2_,rho_)
		{
				dim = dim_;
				estrazioniPassate = std::vector<double>(dim);
				pari = true;
				k = 0;
		}
		~BiVariateJumpDistributionAntitetica(){};

		int operator()(int& x1, int& x2);

};
