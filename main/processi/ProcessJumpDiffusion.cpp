#include "ProcessJumpDiffusion.hpp"
#include "Calibratore.hpp"
#include "VolSurfaceSkew.hpp"
#include "bsformula.hpp"


//ProcessJumpDiffusion::ProcessJumpDiffusion()
//{
//	lambda = 0.1;
//	J = 0.1;
//	sigma = 0.1;
//}

void ProcessJumpDiffusion::generaCammino(double T){}


double ProcessJumpDiffusion::getAssetEvaluation(const Asset *asset, double r, double T) const
{
	return 0;
};

void ProcessJumpDiffusion::calibra(Equity &stock,double riskFreeRate, double horiz)
{
	double spotPrice = stock.getSpot();
	double q = stock.getDividendYield();
	VolSurfaceSkew *skew =(VolSurfaceSkew*)stock.getImplVolSurface();

	vector<double> *K = skew -> getStrikes();
	vector<double> *vols = skew -> getVols();
	vector<double> y((*K).size());
	for (size_t i = 0 ; i < (*vols).size(); i++)
	{
		y[i] = bsprice(spotPrice,(*K)[i]*spotPrice,riskFreeRate,horiz,(*vols)[i],q,1);
	}
	//double initParamsArray[3] = {lambda, J, sigma};
	//vector<double> initParams(initParamsArray,initParamsArray + sizeof(initParamsArray)/sizeof(double));
	vector<double> initParams(3);
	initParams[0] = lambda;
	initParams[1] = J;
	initParams[2] = sigma;

	vector<double> calibratedParams = calibraMerton(initParams,y,(*K),spotPrice,horiz,riskFreeRate);
	lambda = calibratedParams[0];
	J = calibratedParams[1];
	sigma = calibratedParams[2];
}

double* ProcessJumpDiffusion::getParameters()
{
	static double pars[] = {lambda, J, sigma};
//	std::vector<double> pars (3);
//	pars[0]=lambda;
//	pars[1]=J;
//	pars[2]=sigma;
	return pars;
}



	double ProcessJumpDiffusion::getLambda()
{
	return lambda;
}
	double ProcessJumpDiffusion::getJ()
{
	return J;
}
	double ProcessJumpDiffusion::getSigma()
{
	return sigma;
}

