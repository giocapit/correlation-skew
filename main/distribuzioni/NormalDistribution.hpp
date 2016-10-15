#ifndef normalDistr_hpp
#define normalDistr_hpp
#include <vector>
class NormalDistribution
{
	protected:
		double mu, sigma;
	public:
		NormalDistribution(double mu_ = 0.0,
				double sigma_ = 1.0);
		virtual ~NormalDistribution(){};

		virtual double operator()();
		double getNormalByBoxMuller() const; 

};

class NormalDistributionAntitetica:public NormalDistribution
{
	private:
		std::vector<double> estrazioniPassate;
		int dim;
		bool pari;
		int i;
	public:
		NormalDistributionAntitetica(int dim_ = 1,double mu_ = 0.0,
				double sigma_ = 1.0):NormalDistribution(mu_ ,sigma_)
	{
			dim = dim_;
			estrazioniPassate = std::vector<double>(dim);
			pari = true;
			i = 0;
	}
		~NormalDistributionAntitetica(){};

		double operator()() ;

};


class CumulativeNormalDistribution
{
	public:
		CumulativeNormalDistribution(double mu = 0.0,
				double sigma = 1.0);

		~CumulativeNormalDistribution(){};

		double operator()(double x) const;
	private:
		double mu_, sigma_;
				};			
#endif
