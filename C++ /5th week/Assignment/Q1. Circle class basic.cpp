#include <iostream>
using namespace std;

class Circle {
private:
	int x_; int y_; int r_;
	
public:
	Circle() : x_{0}, y_{0}, r_{1} {}
	Circle(int r) : x_ {0}, y_{0}, r_{r} {}
	Circle(int x, int y, int r) : x_{x}, y_{y}, r_{r} {}

	void Move(int x, int y) { x_ += x; y_ += y; }
	void Resize(double r) { r_ = r_ * r; }
	void Draw() { cout << "중심점 : (" << x_ << ", " << y_ << "), 반지름 : " << r_ << endl << "면적 : " << 3.14 * r_ * r_ << endl; }
};

int main()
{
	Circle circle1;
	Circle circle2(100);
	Circle circle3(10, 20, 50);

	circle1.Move(-10, 20);
	circle2.Resize(0.2);

	circle1.Draw();
	circle2.Draw();
	circle3.Draw();
}
