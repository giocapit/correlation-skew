#ifndef Process_hpp
#define Process_hpp

#include "Asset.hpp"

class Process
{
	protected:
		int contatore;
		int maxContatore;
		int dim;

	public:
		Process();
		Process(int N);
		Process(Process* p);
		virtual ~Process();
		virtual double getAssetEvaluation(const Asset *asset, double r, double T) const= 0;
		virtual void generaCammino(double T) = 0;
		virtual void generaCamminiOneShot(double T, int N) = 0;
		void setContatore(int i);
		int getMaxContatore();
		int getDim() const;
		void increaseContatore();
};
#endif
