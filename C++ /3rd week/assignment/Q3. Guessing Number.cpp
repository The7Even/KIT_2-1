#include <iostream>
using namespace std;

int GetArea(int a, int b)
{
	return (a * b);
}

int GetArea(double a)
{
	return (a * a * 3);
}

int main()
{
	int a; int b;
	cout << "input 2 values, input 0 to skip one. : ";
	cin >> a >> b;
	
	if (b != 0)
		cout << "square's Area : " << GetArea(a, b);
	else
		cout << "circle's Area : " << GetArea(a);
}
