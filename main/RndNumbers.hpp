template <class Type> class RndNumbers
{
private:
	Type* numbers;
public:
	RndNumbers();
	RndNumbers(int dim);
	~RndNumbers();

	Type getNumber(int i) const ;

	void setNumber(Type number,int i) ;
};
