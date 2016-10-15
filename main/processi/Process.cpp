#include "Process.hpp"

Process::Process()
{
	contatore = 0;
	maxContatore = 0;
	dim = 0;
}

Process::Process(int N)
{
	contatore = 0;
	maxContatore = 0;
	dim = N;
}

Process::Process(Process* p)
{
	contatore = 0;
	maxContatore = p->getMaxContatore();
	dim = p->getDim();
}


Process::~Process(){};

void Process::setContatore(int i)
{
	contatore = i;
}
int Process::getMaxContatore()
{
	return maxContatore;
}

int Process::getDim() const {
	return dim;
}

void Process::increaseContatore()
{
	contatore = contatore + 1;
}
