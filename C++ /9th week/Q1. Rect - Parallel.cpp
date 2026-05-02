#include <iostream>
#include <string.h>
using namespace std;

class Rectangle {
protected:
	int garo_;
	int sero_;
public:
	Rectangle(int g, int s) : garo_(g), sero_(s) {}
	int getArea() { return garo_ * sero_; }
	void Draw() { cout << "[Rectangle]" << endl << "* 가로 : " << garo_ << endl << "* 세로 : " << sero_ << endl << "* 면적 : " << getArea() << endl; }
};

class Parallelopiped : public Rectangle {
protected:
	int height_;
public:
	Parallelopiped(int g, int s, int h) : Rectangle(g,s), height_(h) {}
	int getVolume() { return getArea() * height_; }
	void Draw() {
		cout << "[Parallelopiped]" << endl << "* 가로 : " << garo_ << endl << "* 세로 : " << sero_ << endl << "* 높이 : " << height_ << endl
			<< "* 밑면적 : " << getArea() << endl << "* 부피 : " << getVolume() << endl;
	}
};

int main() {
	Rectangle rect1(1, 2), rect2(3, 4);
	rect1.Draw();
	rect2.Draw();

	Parallelopiped para1(1, 2, 3), para2(4, 5, 6);
	para1.Draw();
	para2.Draw();
}
