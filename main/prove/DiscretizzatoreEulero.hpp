#include "../ProcessBiVariateLognormal.hpp"

class DiscretizzatoreEuleroLognormale: public ProcessBiVariate
{
private:
	ProcessBiVariateLognormal* process;
public:
	DiscretizzatoreEuleroLognormale(ProcessBiVariateLognormal* p);
	virtual ~DiscretizzatoreEuleroLognormale(){};
	double getAssetEvaluation(const Asset *asset, double r, double T) const;
	void generaCammino(double T);
	void generaCamminoMultiStep(double T){};
	void generaCamminiOneShot(double T, int N);
	void setContatore(int i);
	int getMaxContatore();
	int getDim() const;
	void increaseContatore();
	void setSigma1(double sigma);
	void setSigma2(double sigma);
	void prepareForDestruction();
};
