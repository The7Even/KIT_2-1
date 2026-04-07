#include <iostream>
#include <time.h>
using namespace std;

class Point {
private:
	int x_;
	int y_;
public:
	void SetXY() { x_ = rand() % 201 - 100; y_ = rand() % 201 - 100; }
	void Print() { cout << "(" << x_ << ", " << y_ << ")" << endl; }
};

int main()
{
	srand(time(NULL));
	int amount;

	cout << "갯수 입력 : ";
	cin >> amount;

	Point *ary = new Point[amount];
	
	for (int i = 0; i < amount; i++) { ary[i].SetXY(); ary[i].Print(); }

  delete[] ary;
}
