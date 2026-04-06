#include <iostream>
using namespace std;

class Point {
private:
	int x_;
	int y_;
public:
	Point(int x=0, int y=0) : x_(x), y_(y) {}
	friend void Center(Point pt1, Point pt2);
};

void Center(Point pt1, Point pt2)
{
	Point pt;
	pt.x_ = (pt1.x_ + pt2.x_) / 2; // friend라서 가능한 private 객체 접근
	pt.y_ = (pt1.y_ + pt2.y_) / 2;

	cout << "Center : (" << pt.x_ << ", " << pt.y_ << ")" << endl;
}

int main() {
	Point pt1(2, 3), pt2(4, 7);
	Center(pt1, pt2);
}
