
class LognormalSumDistribution
{
	private:
		double r; 
		double w1; 
		double w2;
	       	double rho;
		double sigma1; 
		double sigma2;

	public:
		LognormalSumDistribution(double r, double w1, double w2, double rho, double sigma1, double sigma2);

		double M1();

		double M2();

		double M3();
};
