#include <iostream>
using namespace std;

int SumofDivisor(int input)
{
	int result = 0;
	for (int i = 1; i < input + 1 ; i++)
	{
		if (input % i == 0)
			result += i;
	}
	return result;
}

int main()
{
	int sum = 0;

	while (1)
	{
		int value;
		cout << "input number(end : 0) : ";
		cin >> value;
		
		if (value == 0)
			break;

		cout <<  "sum of " << value << "'s divisor : " << SumofDivisor(value) << endl;
	}
}
