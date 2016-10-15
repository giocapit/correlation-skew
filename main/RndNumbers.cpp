#include "RndNumbers.hpp"


template<class Type>
RndNumbers<Type>::RndNumbers(int dim)
{
	numbers = new Type[dim];
}

template<class Type>
RndNumbers<Type>::~RndNumbers()
{
	delete [] numbers;
}

template <class Type> Type RndNumbers<Type>::getNumber(int i) const {
	return numbers[i];
}


template <class Type> void RndNumbers<Type>::setNumber(Type number,int i) {
	numbers[i] = number;
}
