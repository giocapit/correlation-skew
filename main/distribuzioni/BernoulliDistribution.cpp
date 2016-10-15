#include "BernoulliDistribution.hpp"
#include "randomGenerator.hpp"
#include <cstdlib>


BernoulliDistribution::BernoulliDistribution(double lambda_)
{
	lambda = lambda_;
	distribution = std::uniform_real_distribution<double> (0.0,1.0);
}

BernoulliDistribution::~BernoulliDistribution() {}


int BernoulliDistribution::operator()()
{
//	double x = rand()/static_cast<double>(RAND_MAX+1);
	double x = distribution(generator);
		if (x < lambda)
			return 1;
		else
			return 0;
}

