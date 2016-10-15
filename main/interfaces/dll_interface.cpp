#include <windows.h>
#include <stdio.h>
#include <ole2.h>

#include "../ProcessBiVariateLognormal.hpp"
#include "calculateCorrelationSkew.hpp"
#include "Equity.hpp"
#include "Basket.hpp"
#include "BasketOption.hpp"
#include "MCOptionPricer.hpp"
#include "bsformula.hpp"


#pragma pack(1)
BOOL APIENTRY Dll_test( HANDLE hModule, DWORD ul_reason_for_call, LPVOID lpReserved )
{
	return TRUE;
}

double * Convert_vector(LPSAFEARRAY FAR *pointer);
void fillSafeArray(LPSAFEARRAY FAR *pointer, double *Value);
// EXAMPLES
extern "C" {

__declspec (dllexport) double __stdcall FooBarRet (double* MyValue,double* output)
{
	double x =*MyValue;
//	double y = static_cast<double>(*MyValue);
//	x = x + y;
	*output = x;
  return x ;
}

__declspec(dllexport) int __stdcall Interface_Implied_Correlation (
		// dati di mercato
		//
		double* vba_Multiplier,
		double* vba_riskFree,
		double* vba_lambda1 ,
		double* vba_J1 ,
		double* vba_sigma1 ,
		double* vba_lambda2 ,
		double* vba_J2 ,
		double* vba_sigma2 ,
		double* vba_rho_merton ,
		double* vba_w1 ,
		double* vba_w2 ,
		double* vba_T ,
		int* vba_num_strikes,
		LPSAFEARRAY FAR * vba_strikes,
		LPSAFEARRAY FAR * vba_results
)
{
	// Dichiarazioni variabili
	//
	double multiplier;
	double riskFree;
	double lambda1 ;
	double J1 ;
	double sigma1 ;
	double lambda2 ;
	double J2 ;
	double sigma2 ;
	double rho_merton ;
	double w1 ;
	double w2 ;
	double T ;
	int num_strikes;
	double strikes1[]={0.70,0.71,0.72,0.73,0.74,0.75,0.76,0.77,0.78,0.79,0.80,0.81,0.82,0.83,0.84,0.85,0.86,0.87,0.88,0.89,0.90,0.91,0.92,0.93,0.94,0.95,0.96,0.97,0.98,0.99,1.00,1.01,1.02,1.03,1.04,1.05,1.06,1.07,1.08,1.09,1.10,1.11,1.12,1.13,1.14,1.15,1.16,1.17,1.18,1.19,1.20,1.21,1.22,1.23,1.24,1.25,1.26,1.27,1.28,1.29,1.30} ;
	double* strikes;
	// Output
	//
	double* result = new double[((*vba_results)->rgsabound->cElements)] ;


	multiplier = *vba_Multiplier;
	riskFree = *vba_riskFree;
	lambda1 = *vba_lambda1 ;
	J1 = *vba_J1 ;
	sigma1 = *vba_sigma1 ;
	lambda2 = *vba_lambda2 ;
	J2 = *vba_J2 ;
	sigma2 = *vba_sigma2 ;
	rho_merton = *vba_rho_merton ;
	w1 = *vba_w1 ;
	w2 = *vba_w2 ;
	T = *vba_T ;
	//num_strikes = *vba_num_strikes;
	num_strikes = static_cast<int>(*vba_num_strikes);
	strikes = Convert_vector(vba_strikes) ;

//	calculateCorrelationSkewJumpDiffusion(	100,
//											0.03,
//											0.5 ,
//											0.6 ,
//											0.2 ,
//											0.1 ,
//											0.5 ,
//											0.3 ,
//											0.5 ,
//											0.3 ,
//											0.7 ,
//											1 ,
//											61,
//											 strikes1 ,
//											 result,
//											 10
//										) ;
	double  result1[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

	fillSafeArray(vba_results, result1) ;
delete [] strikes ;
delete [] result;
	return 0;
}

__declspec(dllexport) int __stdcall Interface_MCPricerLognormal (
		// dati di mercato
		//
		double* vba_riskFree,
		double* vba_sigma1 ,
		double* vba_sigma2 ,
		double* vba_rho,
		double* vba_w1 ,
		double* vba_w2 ,
		double* vba_strike ,
		double* vba_expiry ,
		double* vba_multiplier,
		int* vba_nsim,
		double* vba_price
)
{
	// Dichiarazioni variabili
	//
	double riskFreeRate;
	double sigma1 ;
	double sigma2 ;
	double rho ;
	double w1 ;
	double w2 ;
	double strike;
	double multiplier;
	double expiry;
	int nsim;
	// Output
	//
	double result = 0 ;


	riskFreeRate = *vba_riskFree;
	sigma1 = *vba_sigma1 ;
	sigma2 = *vba_sigma2 ;
	rho = *vba_rho ;
	w1 = *vba_w1 ;
	w2 = *vba_w2 ;
	strike = *vba_strike;
	multiplier = *vba_multiplier;
	expiry = *vba_expiry;
	nsim = *vba_nsim;
	//num_strikes = *vba_num_strikes;
	Equity equity1 = Equity(multiplier);
	Equity equity2 = Equity(multiplier);

	Basket basket = Basket(&equity1, &equity2, w1, w2);
	BasketOption opzione = BasketOption(expiry, &basket,  strike,Option::call);

	ProcessBiVariateLognormal process = ProcessBiVariateLognormal(sigma1,sigma2,rho, nsim);
	MCOptionPricer pricer = MCOptionPricer(&opzione, &process, riskFreeRate , nsim);
	double price = pricer.getOptionPrice();
	*vba_price = price;

	return 0;
}


__declspec(dllexport) double __stdcall Interface_BSprice (
		double vba_spot,
		double vba_riskFree,
		double vba_sigma ,
		double vba_strike ,
		double vba_expiry
)
{
	// Dichiarazioni variabili
	//
	double riskFreeRate;
	double sigma ;
	double strike;
	double spot;
	double expiry;
	// Output
	//

	riskFreeRate = vba_riskFree;
	sigma = vba_sigma ;
	strike = vba_strike;
	spot = vba_spot;
	expiry = vba_expiry;

	double price = bsprice(spot,
			 strike,
			 riskFreeRate,
			 expiry,
			 sigma,
			0,
			1);

	return price;
}

}
double * Convert_vector(LPSAFEARRAY FAR *pointer) {
//	double *pdata ;
//	pdata = (double *)((*pointer)->pvData);
//	double *vector = new double[((*pointer)->rgsabound->cElements)] ;
//	for (int i=0;i<((*pointer)->rgsabound->cElements);i++) {
//		vector[i] = *pdata ;
//		pdata++ ;
//	}
//	return vector ;
	   double* pVals;
	   HRESULT hr = SafeArrayAccessData(*pointer, (void**)&pVals); // direct access to SA memory
	   double *vector;
	   if (SUCCEEDED(hr))
	   {
	     long lowerBound, upperBound;  // get array bounds
	     SafeArrayGetLBound(*pointer, 1 , &lowerBound);
	     SafeArrayGetUBound(*pointer, 1, &upperBound);

	     long cnt_elements = upperBound - lowerBound + 1;
		 vector = new double[cnt_elements];
	     for (int i = 0; i < cnt_elements; ++i)  // iterate through returned values
	     {
	       vector[i] = pVals[i];
	     }
	     SafeArrayUnaccessData(*pointer);
	   }
	   return vector;
}

void fillSafeArray(LPSAFEARRAY FAR *pointer, double *Value)
{
//   int lower0 = (*pointer)->rgsabound->lLbound;
//   int upper0 = (*pointer)->rgsabound->cElements + lower0;
//   double* pData = (double*)(*pointer)->pvData;
//   for(int i = lower0; i < upper0; i++)
//   {
//         *pData = Value[i];
//         pData++;
//   }
   double* pVals;
   HRESULT hr = SafeArrayAccessData(*pointer, (void**)&pVals); // direct access to SA memory
   if (SUCCEEDED(hr))
   {
     long lowerBound, upperBound;  // get array bounds
     SafeArrayGetLBound(*pointer, 1 , &lowerBound);
     SafeArrayGetUBound(*pointer, 1, &upperBound);

     long cnt_elements = upperBound - lowerBound + 1;
     for (int i = 0; i < cnt_elements; ++i)  // iterate through returned values
     {
       pVals[i] = Value[i];
     }
     SafeArrayUnaccessData(*pointer);
   }
}

