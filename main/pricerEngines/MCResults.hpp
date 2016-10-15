#ifndef MCResults_hpp
#define MCResults_hpp

class MCResults
{
protected:
	int payoffNumber;
	double payoffCumulato;
public:
	MCResults(int payoffNumber_);
	virtual ~MCResults();
	virtual void addPayoff(double payoff);
	double getMeanPayoff() const;
	virtual double getMontecarloError() const;

};


class MCResultsErroreMontecarlo: public MCResults
{
protected:
	double payoffQuadroCumulato;
public:
	MCResultsErroreMontecarlo(int payoffNumber_);
	virtual ~MCResultsErroreMontecarlo();
	virtual void addPayoff(double payoff);
	virtual double getMontecarloError() const;

};

class MCResultsErroreMontecarloAntitetico: public MCResultsErroreMontecarlo
{
protected:
	double payoffCammino1;
	bool pari;
public:
	MCResultsErroreMontecarloAntitetico(int payoffNumber_);
	~MCResultsErroreMontecarloAntitetico();
	void addPayoff(double payoff);
	double getMontecarloError() const;

};
#endif
