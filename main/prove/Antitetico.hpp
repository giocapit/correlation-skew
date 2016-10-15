#ifndef Antitetico_hpp
#define Antitetico_hpp

#include "Process.hpp"

class Antitetico:public Process
{
	private:
		Process* p;

	public:
		Antitetico();
		Antitetico(int N);
		Antitetico(Process* p_);
		virtual ~Antitetico();
		double getAssetEvaluation(const Asset *asset, double r, double T) const{return 0;};
		void generaCammino(double T);
		void generaCamminiOneShot(double T, int N){};
		void generaCamminoSpeculare(){};
		void setContatore(int i);
		int getMaxContatore();
		int getDim() const;
		void increaseContatore();
};
#endif
