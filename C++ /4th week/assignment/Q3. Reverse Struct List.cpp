#include <iostream>
using namespace std;

struct Point
{
	int x;
	int y;
};

void Reverse(Point* ary, int len)
{
	int minus = 0;
	if (len % 2 == 1)
		minus = 1;
	Point temp;
	for (int i = 0; i < (len - minus) / 2; i++)
	{
		temp = ary[i];
		ary[i] = ary[len - i - 1];
		ary[len - i - 1] = temp;
	}
}

int main()
{
	Point pt[5] = { { 5, 2 }, { 2, 2 }, { 8, 1 }, { 1, 1 }, { 5, 5 } };
	Reverse(pt, 5);

	for (int i = 0; i < 5; i++)
		cout << "pt[" << i << "] (" << pt[i].x << ", " << pt[i].y << ")" << endl;

}
