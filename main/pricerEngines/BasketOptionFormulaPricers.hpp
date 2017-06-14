#ifndef basket_option_formula_price_hpp
#define basket_option_formula_price_hpp
#include "OptionPricer.hpp"
#include "BasketOption.hpp"
#include "Functional.hpp"
#include "LognormalDistribution.hpp"

class BSBasketOptionPricer: public OptionPricer
{
	public:
		BSBasketOptionPricer(const BasketOption *opzione, Process *processo, double riskFreeRate): OptionPricer(opzione, processo, riskFreeRate){};

		~BSBasketOptionPricer(){};

		double getOptionPrice();
};

class GeneralizedBSBasketOptionPricer: public OptionPricer
{
	public:
		GeneralizedBSBasketOptionPricer(const BasketOption *opzione, Process *processo, double riskFreeRate): OptionPricer(opzione, processo, riskFreeRate){};

		~GeneralizedBSBasketOptionPricer(){};

		double getOptionPrice();

		class Functional4MomentsCalculation : public MultiFunctional
	{
		private:
			double phiM1;
			double phiM2;
			double phiM3;


		public:
			Functional4MomentsCalculation(double phiM1, double phiM2, double phiM3):MultiFunctional()
		{
			this->phiM1 = phiM1;
			this->phiM2 = phiM2;
			this->phiM3 = phiM3;
		}
			std::vector<double> operator()(const std::vector<double> & x) const;

	};

		class Jacobian4MomentsCalculation: public MultiFunctional
	{
		public:
			std::vector<double> operator()(const std::vector<double> & x) const;
	};
		
		class Functional4MomentsCalculation2 : public MultiFunctional
	{
		private:
			double phiM1;
			double phiM2;
			double phiM3;
			double phiM4;


		public:
			Functional4MomentsCalculation2(double phiM1, double phiM2, double phiM3, double phiM4):MultiFunctional()
		{
			this->phiM1 = phiM1;
			this->phiM2 = phiM2;
			this->phiM3 = phiM3;
			this->phiM4 = phiM4;
		}
			std::vector<double> operator()(const std::vector<double> & x) const;

	};
		class Functional4MomentsCalculation3 : public MultiFunctional
	{
		private:
			double phiM1;
			double phiM2;
			double phiM3;
			double phiM4;


		public:
			Functional4MomentsCalculation3(double phiM1, double phiM2, double phiM3, double phiM4):MultiFunctional()
		{
			this->phiM1 = phiM1;
			this->phiM2 = phiM2;
			this->phiM3 = phiM3;
			this->phiM4 = phiM4;
			this->dim_y = 4;
		}
			std::vector<double> operator()(const std::vector<double> & x) const;

	};

};

#endif
