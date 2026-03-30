#include <iostream>
using namespace std;

class Point {
private:
	int x_;
	int y_;

public:
	Point(int x, int y) { x_ = x; y_ = y; }
	Point(int x) { x_ = x; y_ = 0; }
	Point() { x_ = 0; y_ = 0; }
	~Point() { cout << "소멸자: "; Print(); } // 소멸 순서는 stack 구조라 FILO 법칙을 따른다.
	void Print() { cout << "(" << x_ << ", " << y_ << ")" << endl; }
};

class Array { // 항상 이러한 클래스 객체에서는 Default 생성자가 존재한다.
	// Array() {} // 이런식으로 Default 생성자가 암묵적으로 존재한다.
	// ~Array() {} // 이런식으로 Default 소멸자도 암묵적으로 존재한다는거.
	// 근데 물론 얘는 해당 안된다. public에 생성자가 있어서 Default 생성자가 소멸했기 때문.
private:
	int count_;
	int* ary_;

public:
	Array(int count) { count_ = count; ary_ = new int[count_]; } // < 생성자
	~Array() { cout << count_ << " 길이의 배열이 소멸됨"<< endl; } // < 소멸자
	void Delete() { delete[] ary_; } // < 자멸
	void Print() { for (int i = 0; i < count_; i++) cout << ary_[i] << endl; }
};

class NewType {
private:
	int x_;
	int y_;

public:
	NewType(int x, int y) : x_(x), y_(y) {}
	// NewType(int x, int y) { x_ = x; y_ = y; } 와 같은 구문. 하지만 생성과 동시에 초기화도 되기에 주석의 이 구문보다 더 낫다.
	void Print() { cout << "(" << x_ << ", " << y_ << ")" << endl; }
};

int main()
{
	Point pt1(3, 2);
	Point pt2(6);
	Point pt3;

	pt1.Print();
	pt2.Print();
	pt3.Print();

	Array ary(5);
	ary.Print();
	ary.Delete();

	// Array ary2; << 이거 에러난다. 26번줄에 생성자가 있어서 그렇다.
	// Array class에 Array () {} 이거 수동으로 넣어주면 해결된다.
}
