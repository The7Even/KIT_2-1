#include <iostream>
using namespace std;

void MaxMin(int *a, int *b)
{
	int temp;
	if (*a < *b)
	{
		temp = *a;
		*a = *b;
		*b = temp;
	}
}

int main()
{
	int max, min;
	cout << "Input 2 Numbers. : ";
	cin >> max >> min;

	MaxMin(&max, &min);

	cout << "Max : " << max << endl;
	cout << "Min : " << min << endl;
}
