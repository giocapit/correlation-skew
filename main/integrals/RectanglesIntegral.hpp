#include <functional>


class RectanglesIntegral
{
	private:
		int n;
	public:
		RectanglesIntegral(int n){ this->n = n; };
		~RectanglesIntegral(){};

		double integrate(const std::function<double(double)>& integrand , 
				double a,
				double b);
};
