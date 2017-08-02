
#include <vector>
#include <iostream>
#include "prova.hpp"
int main ()
{
	int i = 0;
	//Constraints constraints({0}, {-0.01}, {0.3});
	std::vector<double> index(1,0.0);
	std::vector<double> doub(1,-0.01);
	std::vector<double> ter(1,0.3);
	Prova prova(index);
	return 0;
}
