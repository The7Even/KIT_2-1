#include <iostream>
using namespace std;

class Point {
private:
	int x_, y_;
public:
	Point(int x, int y) : x_(x), y_(y) {}
	Point(int x) : x_(x), y_(0) {}
	Point() : x_(0), y_(0) {}
	void print() { cout << "(" << x_ << ", " << y_ << ")" << endl; }
	void setXY(int x, int y) { x_ = x; y_ = y; }
	int getX() { return x_; }
	int getY() { return y_; }
	Point moveXY(int x, int y) { x_ += x; y_ += y; return (*this); } // this 포인터 사용법
};

int GetsumX(Point ary[], int len)
{
	int dump = 0;
	for (int i = 0; i < len; i++)
		dump += ary[i].getX();

	return dump;
}

int GetsumY(Point ary[], int len)
{
	int dump = 0;
	for (int i = 0; i < len; i++)
		dump += ary[i].getY();

	return dump;
}

int main() {
	Point ptlist[5] = { Point(3, 5) , Point(2,6), Point(8), Point(6,7), Point(8,2)};
	for (int i = 0; i < 5; i++)
		ptlist[i].print();

	ptlist[0].moveXY(1,2).moveXY(4,5); // 이렇게 해도 가능함. this 포인터 return해주면 가능함.

	Point sum(GetsumX(ptlist, 5), GetsumY(ptlist, 5));
	sum.print();
}
