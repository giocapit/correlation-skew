#include <Antitetico.hpp>

double Antitetico::getAssetEvaluation(const Asset* asset, double r,
		double T) const
{
	return p->getAssetEvaluation(asset,r,T);
}

void Antitetico::generaCammino(double T)
{
	if((p->getMaxContatore())%2)
	{
		p->generaCammino(T);
	}else{
		p->generaCamminoSpeculare();
	}
}

void Antitetico::generaCamminiOneShot(double T, int N)
{
	p->generaCamminiOneShot(T,N);
}

void Antitetico::setContatore(int i)
{
	p->setContatore(i);
}
int Antitetico::getMaxContatore()
{
	return p->getMaxContatore();
}
int Antitetico::getDim()const
{
	return p->getDim();
}
void Antitetico::increaseContatore()
{
	p->increaseContatore();
}
