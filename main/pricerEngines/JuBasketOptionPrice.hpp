#ifndef ju_basket_option_formula_price_hpp
#define ju_basket_option_formula_price_hpp
#include "OptionPricer.hpp"
#include "BasketOption.hpp"
#include "NbasketOption.hpp"
#include "Functional.hpp"
#include "LognormalDistribution.hpp"
#include "BasketOptionFormulaPricers.hpp"

class JuBasketOptionPricer: public BSBasketOptionPricer
{
	public:
		JuBasketOptionPricer(const BasketOption *option, Process *process, double riskFreeRate);

		JuBasketOptionPricer(const NbasketOption *option, Process *process, double riskFreeRate);

		~JuBasketOptionPricer(){};

		double getOptionPrice();

	private:
		double strike;

		double p(double x);
		double p_dx(double x);
		double p_dxx(double x);
		double sigma1;
		double sigma2;
		double rho;
		double w1;
		double w2;
		std::vector<double> * sigma;
		std::vector<vector<double>> * rhoMatrix;
		const std::vector<double> * weights;

		double multiplier;
		double m;
		double s;
		double U1;
		double U2;

		struct coefficients{
			double dU2 ;
			double d2U2;
			double d3U2;
			double b1;
			double k1;
			double k2;
			double q1;
			double q2;
			double multiplier;
			coefficients(double multiplier);
		};
		coefficients coeffs;

		struct coeff_for_2basket: coefficients {
			double w1;
			double w2;
			double rho;
			double sigma1;
			double sigma2;
			coeff_for_2basket(double multiplier,
						double w1,
						double w2,
						double sigma1,
						double sigma2,
						double rho,
						double riskFreeRate);
		};

		struct coeff_for_Nbasket: coefficients {

			std::vector<double> * sigma;
			std::vector<vector<double>> * rhoMatrix;
			const std::vector<double> * weights;
			coeff_for_Nbasket(double multiplier, 
					std::vector<double> * sigma,
					std::vector<vector<double>> * rhoMatrix,
					const std::vector<double> * weights,
					double riskFreeRate);
		};

};    
#endif
