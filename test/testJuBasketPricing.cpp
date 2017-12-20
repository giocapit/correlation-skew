#include "BasketOptionFormulaPricers.hpp"
#include "JuBasketOptionPrice.hpp"
#include "MCOptionPricer.hpp"
#include "Equity.hpp"
#include "NbasketOption.hpp"
#include "ProcessNVariateLognormal.hpp"
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

	double eqValue = 100;
	double w1 ;
	double w2 ;
	double w3 ;
	double w4 ;
	double w5 ;
	double strike ;
	double expiry ;
	double riskFreeRate ;
	Option::type cp = Option::call;

	ifstream testBook ("testBook1.csv", fstream::in);
	double juprice;
	string line;
	//discard the header line
	getline(testBook, line);

	while(getline(testBook, line))
	{
		vector<string> parsedLine = split(line, ';');
		w1 = stod(parsedLine[0]);
		w2 = stod(parsedLine[1]);
		w3 = stod(parsedLine[2]);
		w4 = stod(parsedLine[3]);
		w5 = stod(parsedLine[4]);
		vector<double> weights = {w1,w2,w3,w4,w5};	

		double multiplier = 0;
		for (int i=0; i < 5; ++i)
		{
			multiplier += weights[i] * eqValue;
		}

		strike = stod(parsedLine[5]);
		vector<double> sigma(5, stod(parsedLine[6]));
		double rho = stod(parsedLine[7]);
		expiry = stod(parsedLine[8]);
		riskFreeRate = stod(parsedLine[9]);
		
		Nbasket basket = Nbasket(multiplier,weights);
		NbasketOption opzione = NbasketOption(expiry, &basket,  strike,cp);

		ProcessNVariateLognormal process = ProcessNVariateLognormal(5,sigma,rho);
		JuBasketOptionPricer juoptionpricer = JuBasketOptionPricer(& opzione, &process, riskFreeRate); 
		juprice = juoptionpricer.getOptionPrice();

		cout << juprice << endl
			<< "\n" << endl;
	}


	return 0;

}

