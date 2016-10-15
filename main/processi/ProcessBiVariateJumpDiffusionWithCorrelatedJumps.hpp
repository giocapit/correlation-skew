#ifndef process_bi_variate_jump2_hpp
#define process_bi_variate_jump2_hpp
#include "ProcessBiVariate.hpp"
#include "BiVariateJumpDistribution.hpp"
#include "Basket.hpp"

class ProcessBiVariateJumpDiffusionWithCorrelatedJumps: public ProcessBiVariate
{
	private:
		//parametri che definiscono la dinamica
		double rho_diffusion;
		double rho_jump;
		double lambda1;
		double J1;
		double sigma1;
		double lambda2;
		double J2;
		double sigma2;

		BiVariateJumpDistribution* X;

		//vettori che registrano le realizzazioni della variabile che modellizza l'eventualità di un salto
		vector<double> *X1;
		vector<double> *X2;

	public:
		ProcessBiVariateJumpDiffusionWithCorrelatedJumps(double lambda1_,
						double J1_,
						double sigma1_,
						double lambda2_,
						double J2_,
						double sigma2_,
						double rho_diffusion_,
						double rho_jump_,
						int N,
						int dim):
			ProcessBiVariate(N,dim)
		{
			lambda1 = lambda1_;
			lambda2 = lambda2_;
			J1 = J1_;
			J2 = J2_;
			sigma1 = sigma1_;
			sigma2 = sigma2_;
			rho_diffusion = rho_diffusion_;
			rho_jump = rho_jump_;
			double dt = 1.0/dim;

//			X = new BiVariateJumpDistribution(lambda1 * dt,lambda2 * dt, rho_jump);
			X = new BiVariateJumpDistributionAntitetica(lambda1 * dt,lambda2 * dt, rho_jump,dim);

			X1 = new vector<double>[N];
			X2 = new vector<double>[N];
			for (int i = 0; i<N; i++)
			{
				X1[i].reserve(dim);
				X2[i].reserve(dim);
			}
		};

		ProcessBiVariateJumpDiffusionWithCorrelatedJumps(double lambda1_,
						double J1_,
						double sigma1_,
						double lambda2_,
						double J2_,
						double sigma2_,
						double rho_diffusion_,
						double rho_jump_,
						NormalDistribution* N1_,
						NormalDistribution* N2_,
						BiVariateJumpDistribution* X_,
						int N,
						int dim):
			ProcessBiVariate(N,dim)
		{
			lambda1 = lambda1_;
			lambda2 = lambda2_;
			J1 = J1_;
			J2 = J2_;
			sigma1 = sigma1_;
			sigma2 = sigma2_;
			rho_diffusion = rho_diffusion_;
			rho_jump = rho_jump_;
			N1 = N1_;
			N2 = N2_;
			X = X_;
//			double dt = 1.0/dim;

//			X = new BiVariateJumpDistribution(lambda1 * dt,lambda2 * dt, rho_jump);

			X1 = new vector<double>[N];
			X2 = new vector<double>[N];
		};


		~ProcessBiVariateJumpDiffusionWithCorrelatedJumps()
		{
			delete[] X1;
			delete[] X2;
			delete X;
		};

		void calibra(Basket &basket,double riskFreeRate, double T);
		void generaCammino(double T);
		void generaCamminiOneShot(double T, int N);
		double getAssetEvaluation(const Asset *asset,
				double r,
				double T) const;

		bool useEulerToCalculateCorrelation(){return true;}

	double getRhoDiffusion() const {
		return rho_diffusion;
	}

	double getRhoJump() const {
		return rho_jump;
	}
};

#endif
