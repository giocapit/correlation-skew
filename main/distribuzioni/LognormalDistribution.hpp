#ifndef lognormaldistribution_hpp
#define lognormaldistribution_hpp



class LogNormalDistribution
{
	private:
		double tau;
		double m;
		double s;
		double M_1;
		double M_2;
		double M_3;

	public:
		LogNormalDistribution(double tau, double m, double s);
		void setParams(double tau, double m, double s);

		double M1() const;
		double M2() const;
		double M3() const;


		static double M1(double tau, double m, double s);
		static double M2(double tau, double m, double s);
		static double M3(double tau, double m, double s);

		double getTau() const;

};

#endif
