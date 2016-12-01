#include <stdio.h>


extern "C" {

int FooBarRet (int* MyValue,double* output)
{
	double x =100.0;
	double y = static_cast<double>(*MyValue);
	x = x + y;
	*output = x;
  return 0 ;
}

double sum (double* a)
{
	return a[0]+a[1];
}
}
