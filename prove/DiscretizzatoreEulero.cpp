DiscretizzatoreEuleroLognormale::DiscretizzatoreEuleroLognormale(ProcessBiVariateLognormal* p)
{
	process = p;
}

double DiscretizzatoreEuleroLognormale::getAssetEvaluation(const Asset *asset, double r, double T)const
{
	return process->getAssetEvaluationEulero(asset, r, T);
}

void DiscretizzatoreEuleroLognormale::generaCammino(double T)
{
	process->generaCamminoMultiStep(T);
}

void DiscretizzatoreEuleroLognormale::generaCamminiOneShot(double T, int N){};

void DiscretizzatoreEuleroLognormale::setContatore(int i)
{
	process->setContatore(i);
}

int DiscretizzatoreEuleroLognormale::getMaxContatore()
{
	return process->getMaxContatore();
}

int DiscretizzatoreEuleroLognormale::getDim() const
{
	return process->getDim();
}

void DiscretizzatoreEuleroLognormale::increaseContatore()
{
	process->increaseContatore();
}

void DiscretizzatoreEuleroLognormale::setSigma1(double sigma)
{
	process->setSigma1(sigma);
}
void DiscretizzatoreEuleroLognormale::setSigma2(double sigma)
{
	process->setSigma1(sigma);
}

void DiscretizzatoreEuleroLognormale::prepareForDestruction()
{
	process->prepareForDestruction();
}



