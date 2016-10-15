#ifndef Bernoulli_hpp
#define Bernoulli_hpp
#include <random>

class BernoulliDistribution
{
	protected:
		double lambda;
		std::uniform_real_distribution<double> distribution;


	public:
		BernoulliDistribution(double lambda_ = 0.0);
		~BernoulliDistribution();

		int operator()() ;
};
#endif
