#ifndef process_bi_variate_jump_hpp
#define process_bi_variate_jump_hpp
#include "ProcessBiVariate.hpp"
#include "PoissonDistribution.hpp"
#include "Basket.hpp"

class ProcessBiVariateJumpDiffusion: public ProcessBiVariate
{
	private:
		double rho;
		double lambda1;
		double J1;
		double sigma1;
		double lambda2;
		double J2;
		double sigma2;

		PoissonDistribution* P1;
		PoissonDistribution* P2;

		vector<int> *X1;
		vector<int> *X2;

	public:

		ProcessBiVariateJumpDiffusion(double lambda1_,
						double J1_,
						double sigma1_,
						double lambda2_,
						double J2_,
						double sigma2_,
						double rho_):
			ProcessBiVariate()
		{
			lambda1 = lambda1_;
			lambda2 = lambda2_;
			J1 = J1_;
			J2 = J2_;
			sigma1 = sigma1_;
			sigma2 = sigma2_;
			rho = rho_;

			P1 = new PoissonDistribution(lambda1);
			P2 = new PoissonDistribution(lambda2);


			X1 = NULL;
			X2 = NULL;
		};

		ProcessBiVariateJumpDiffusion(double lambda1_, 
						double J1_,	
						double sigma1_,
						double lambda2_,
						double J2_,
						double sigma2_,
						double rho_,
						int N):
			ProcessBiVariate(N)
		{
			lambda1 = lambda1_;
			lambda2 = lambda2_;
			J1 = J1_;
			J2 = J2_;
			sigma1 = sigma1_;
			sigma2 = sigma2_;
			rho = rho_;

			P1 = new PoissonDistribution(lambda1);
			P2 = new PoissonDistribution(lambda2);


			X1 = new vector<int>[N];
			X2 = new vector<int>[N];
		};

		~ProcessBiVariateJumpDiffusion()
		{
			delete P1;
			delete P2;
			delete[] X1;
			delete[] X2;
		};
		
		void generaCammino(double T);
		void generaCamminiOneShot(double T, int N);
		double getAssetEvaluation(const Asset *asset, 
				double r,
				double T) const;
		void allocateRandomVariables(int N);
		bool useEulerToCalculateCorrelation(){return false;}

};

#endif
