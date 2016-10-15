#include "ProcessBiVariate.hpp"
#include <stdio.h>

//double ProcessBiVariate::getNewPrice(Basket *basket,
//		double r,
//		double T)
//{
//
//	//double S01 = basket->getAsset1()->getSpot();
//	//double S02 = basket->getAsset2()->getSpot();
//	double multiplier = basket->getMultiplier();
//	double newIndexLevel = getAssetEvaluation(basket, r, T);
//	double price = newIndexLevel * multiplier;
//	return price;
//}

vector<double>* ProcessBiVariate::getZ1()
{
	return Z1;
}

vector<double>* ProcessBiVariate::getZ2()
{
	return Z2;
}


void ProcessBiVariate::prepareForDestruction()
{
	Z1 = NULL;
	Z2 = NULL;

}

void ProcessBiVariate::allocateRandomVariables(int N)
{
	Z1 = new vector<double>[N];
	Z2 = new vector<double>[N];
}
