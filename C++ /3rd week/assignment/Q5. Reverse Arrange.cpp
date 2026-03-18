#include <iostream>
using namespace std;

void Reverse(int* ary, int len)
{
	int minus = 0;
	if (len % 2 == 1)
		minus = 1;
	int temp;
	for (int i = 0; i < (len - minus) / 2; i++)
	{
		temp = ary[i];
		ary[i] = ary[len - i-1];
		ary[len - i-1] = temp;
	}
}

int main()
{
	int ary[5] = { 6,3,9,2,7 };
	Reverse(ary, 5);

	for (int i = 0; i < 5; i++)
		cout << ary[i] << " ";
}
