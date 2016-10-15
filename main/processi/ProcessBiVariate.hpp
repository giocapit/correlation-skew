#ifndef procBiVar_hpp
#define procBiVar_hpp
#include "Process.hpp"
#include "NormalDistribution.hpp"
#include "RndNumbers.hpp"
#include <cstdio>
#include <vector>

using namespace std;
class ProcessBiVariate: public Process
{
	protected:
		NormalDistribution* N1;
		NormalDistribution* N2;
		vector<double> *Z1;
		vector<double> *Z2;

	public:

		ProcessBiVariate():Process()
		{
			N1 = new NormalDistribution();
			N2 = new NormalDistribution();
			Z1 = NULL;
			Z2 = NULL;
		};

		ProcessBiVariate(int N):Process(1)
		{
			N1 = new NormalDistributionAntitetica();
			N2 = new NormalDistributionAntitetica();
			Z1 = new vector<double>[N];
			Z2 = new vector<double>[N];
		};

		ProcessBiVariate(int N, int dim):Process(dim)
		{
			N1 = new NormalDistributionAntitetica(dim);
			N2 = new NormalDistributionAntitetica(dim);
			Z1 = new vector<double>[N];
			Z2 = new vector<double>[N];
		};

		ProcessBiVariate(ProcessBiVariate* p):Process(p)
		{
			N1 = new NormalDistribution();
			N2 = new NormalDistribution();
			Z1 = p ->getZ1();
			Z2 = p ->getZ2();
		};

		ProcessBiVariate(int N, NormalDistribution *N1_, NormalDistribution *N2_):Process(1)
		{
			N1 = N1_;
			N2 = N2_;
			Z1 = new vector<double>[N];
			Z2 = new vector<double>[N];
		};

		ProcessBiVariate(int N, int dim, NormalDistribution *N1_, NormalDistribution *N2_):Process(dim)
		{
			N1 = N1_;
			N2 = N2_;
			Z1 = new vector<double>[N];
			Z2 = new vector<double>[N];
		};

		~ProcessBiVariate()
		{
			delete N1;
			delete N2;
			delete[] Z1;
			delete[] Z2;
		};

		void allocateRandomVariables(int N);
		void prepareForDestruction();
		
		/*void generaCammino();*/
//		double getNewPrice(Basket *basket,
//				double r,
//				double T);

		vector<double>* getZ1();
		vector<double>* getZ2();

		virtual bool useEulerToCalculateCorrelation()=0;


};
#endif
