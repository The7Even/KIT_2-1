#include <iostream>
using namespace std;

#define MAIN_CPP
#include "headerTest.h"

class Car {
public:
	int color;
	int cc;
	void Stop() { speed = 0; } // 이렇게 하면 이 함수로만 speed에 접근 가능함

private:
	int speed;
};

class pos {
public:
	void SetXY(int a, int b) { x = a; y = b; }
	void Print() { cout << "(" << x << ", " << y << ")" << endl; }
	void Move(int a, int b) { x += a; y += b; }

private:
	int x;
	int y;
};

int main()
{
	// Point pt1 = { 3, 4 };
	// num = 100; // headerTest.h 에서 extern int num; 으로 정의가 되어있음.
	// Print(pt1);

	pos pos1;
	
	// pos1.x = 5; // 이러면 ERROR
	pos1.SetXY(4,7);
	pos1.Move(3, 3);
	pos1.Print();

}
