#include <iostream>
#include <string.h>
using namespace std;

class Calculator {
protected:
	double result_;
public:
	Calculator() { result_ = 0; }
	void Add(double a, double b) { result_ = a + b; }
	void Add(double a) { result_ += a; }
	void Sub(double a, double b) { result_ = a - b; }
	void Sub(double a) { result_ -= a; }
	void Print() { cout << "*** Result : " << result_ << endl; }
};

class AdvancedCal : public Calculator {
protected:
	string Brand_;
public:
	AdvancedCal(string Brand) : Brand_(Brand) { result_ = 0; }
	void Mul(double a, double b) { result_ =  a* b; }
	void Mul(double a) { result_ *= a; }
	void Div(double a, double b) { 
		if (b != 0)
			result_ = a / b;
		else
			cout << "Div0 ERROR" << endl;
	}
	void Div(double a) {
		if (a != 0)
			result_ /= a;
		else
			cout << "Div0 ERROR" << endl;
	}
	void Print() { cout << "[brand : " << Brand_ << "]" << endl << "*** Result : " << result_ << endl; }
};

int main()
{
	Calculator calc1;
	calc1.Add(10, 20);
	calc1.Add(100);
	calc1.Print();

	AdvancedCal calc2("Samsung");
	calc2.Mul(3, 5);
	calc2.Mul(7);
	calc2.Add(100);
	calc2.Print();
}
