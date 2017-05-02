#include "Process.hpp"
#include "Equity.hpp"
#include <cstdlib>
#include <vector>


class Calibratore
{
	public:
		
		struct data 
		{
			size_t n;
			double *y;
			double *K;
		};
		void calibra(vector<double> x, vector<double> y);
	private:

		Equity *asset;
		Process *process;
		

};


