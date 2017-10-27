#include "BasketOptionFormulaPricers.hpp"
#include "CurranBasketOptionPricer.hpp"
#include "MCOptionPricer.hpp"
#include "Equity.hpp"
#include "BasketOption.hpp"
#include "ProcessBiVariateLognormal.hpp"
#include "LognormalSumDistribution.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <iterator>

template<typename Out>
void split(const std::string &s, char delim, Out result) {
    std::stringstream ss;
    ss.str(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        *(result++) = item;
    }
}

std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, std::back_inserter(elems));
    return elems;
}

using namespace std;

int main()
{

	int nSim= 1000000;
	double multiplier = 1;
	double w1 ;
	double w2 ;
	double strike ;
	double sigma1 ;
	double sigma2 ;
	double rho ;
	double expiry ;
	double riskFreeRate ;
	Option::type cp = Option::call;

	ifstream testBook ("testBook.txt", fstream::in);
	Equity equity1 = Equity(multiplier);
	Equity equity2 = Equity(multiplier);
	double mcprice;
	double bsprice;
	double curranprice;
	string line;
	//discard the header line
	getline(testBook, line);

	while(getline(testBook, line))
	{
		vector<string> parsedLine = split(line, ';');
		w1 = stod(parsedLine[0]);
		w2 = stod(parsedLine[1]);
		strike = stod(parsedLine[2]);
		sigma1 = stod(parsedLine[3]);
		sigma2 = stod(parsedLine[4]);
		rho = stod(parsedLine[5]);
		expiry = stod(parsedLine[6]);
		riskFreeRate = stod(parsedLine[7]);
		
		Basket basket = Basket(&equity1, &equity2, w1, w2);
		BasketOption opzione = BasketOption(expiry, &basket,  strike,cp);

		NormalDistributionAntitetica* N1 = new NormalDistributionAntitetica();
		NormalDistributionAntitetica* N2 = new NormalDistributionAntitetica();

		ProcessBiVariateLognormal process = ProcessBiVariateLognormal(sigma1,sigma2,rho, nSim, N1, N2);
		//cout << process.getSigma1();
		//cout << process.getSigma2();
		MCOptionPricer montecarlopricer = MCOptionPricer(&opzione,
				&process,
				riskFreeRate ,
				nSim);
		BSBasketOptionPricer bsoptionpricer = BSBasketOptionPricer(& opzione, &process, riskFreeRate); 
		CurranBasketOptionPricer curranoptionpricer = CurranBasketOptionPricer(& opzione, &process, riskFreeRate); 
		mcprice = montecarlopricer.getOptionPrice();
		bsprice = bsoptionpricer.getOptionPrice();
		curranprice = curranoptionpricer.getOptionPrice();

		cout << mcprice << endl
			<< bsprice << endl
			<< curranprice << endl;
	}


	return 0;

}

