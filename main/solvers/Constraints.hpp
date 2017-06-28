#ifndef Constraints_hpp
#define Constraints_hpp
#include <vector>
#include <iostream>

class Constraints
{
	private:
		std::vector<int> index;
		std::vector<double> upperBound;
		std::vector<double> lowerBound;

	public:
		Constraints(const std::vector<int> & _index, 
				const std::vector<double> & _upperBound, 
				const std::vector<double> & _lowerBound):
		
			index{ _index},
			upperBound{_upperBound},
			lowerBound{_lowerBound}
			{

				printf("%5f", upperBound[0]);
				std::cout << index[0];

		};

		~Constraints(){};
		

		std::vector<double> update(std::vector<double> x);
};
#endif
