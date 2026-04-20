#include <iostream>
using namespace std;

class Point {
private:
	int x_;
	int y_;
	int editID_ = 0; // 멤버 초기화 구문 예시

public:
	Point(int x) : x_(x), y_(10) {} // 오버로딩된거. 요소 갯수에 따라서 구분이 가능해야 함.
	Point(int x = 0, int y = 0) : x_(x), y_(y) {} // 생성자, Default 매개변수가 적용되어 있음.
	
	~Point() { cout << "Point Deleted." << endl; } // 소멸자

	Point Sum(int x, int y)
	{
		x_ += x;
		y_ += y;

		return (*this);
	}

	int ReturnX() { return x_; }
	int ReturnY() { return y_; }

	int moveX(int x);

	void PrintXY() { cout << "(" << x_ << ", " << y_ << ")" << endl; }

	friend void EditXY(Point pt, int x, int y);
};

void EditXY(Point pt, int x, int y)
{
	static int editTimes = 0; // static은 처음 함수 실행 1회차에만 적용됨.
	editTimes++;
	pt.x_ = x;
	pt.y_ = y;
	pt.editID_ = editTimes; // 그럼 얘는 수정된 횟수가 ID로써 기록됨.
}

int Point::moveX(int x) { // 멤버 함수의 외부 선언 예제
	x_ += x;
}

class Array
{
private:
	Point pt_; // 다른 객체를 이렇게 가지고 있을수 있대요

public:
	int returnPoint()
	{
		pt_.PrintXY(); // 이렇게 함수도 사용 가능
	}
};

class List
{
private:
	int size_;
	int* ary_;

public:
	List(const List& lst) // 복사 생성자 예시
	{
		size_ = lst.size_;

		if (size_ > 0)
		{
			ary_ = new int[size_];
			for (int i = 0; i < size_; i++)
				ary_[i] = lst.ary_[i];
		}
		else
			ary_ = NULL;

	}
};

int main()
{
	// 1. cin & cout
	int cintester = 0;
	cout << "숫자를 입력 : ";
	cin >> cintester;
	cout << cintester << endl << endl;

	// 2. 범위 기반 for 문
	int ary1[] = {1,2,3,4};
	for (int i : ary1)
		cout << i << endl;
	cout << endl;

	// 3. 포인터 & 참조
	int* ary2 = new int[5];
	// 참조 코드 어캐쓸지 생각안나서 걍 &로 쓴다는거만 적어놓고 튐 ㅅㄱ

	delete[] ary2;

	// 4. 람다 함수
	int (*sum)(int x, int y) = [](int x, int y) -> int { return x + y; };

	cout << sum(3, 5) << endl << endl;

	// 5. private & public 멤버
	Point pt1(1, 2);
	pt1.PrintXY();
	// pt1.x_ = 9; << private  멤버에 대해서 접근이 제한됨

	// 6. 생성자와 소멸자
	// 는 Point class에 구현 완료 (각 Point(int x=-0,,,뭐시기)

	// 7. 함수 오버로딩
	// 도 역시 Point class에 구현해버리기

	// 8. Default 매개변수
	// 생성자에 해놨네

	// 9. this 포인터
	// 얘도 Point class에 구현하기
	cout << endl;
	pt1.Sum(1, 1).Sum(2, 2);
	pt1.PrintXY();

	// 10. 멤버함수의 내부, 외부 정의
	// 안에서 정의하면 내부고 밖에서 정의하면 외부임
	// 밖에서 정의할경우 객체 안에 ProtoType 남겨놓고 밖에서 따로 선언하면 됨.

	// 11. 멤버 초기화 구문
	// 더미 데이터 z_를 만들어 구현했음. >> edit_로 변경

	// 12. 메모리 동적 할당 (new, delete)인데 3번에서 했음...

	// 13. 클래스 객체 배열
	Array* Arraylist = new Array[5]; // 별도의 초기화가 필요없이 전부다 NULL값으로 초기화.
	Point* Pointlist = new Point[5]; // YEAHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH

	// 14. 클래스 객체 포인터, 이중포인터
	Point* ptpt = &pt1; // 클래스 객체 포인터. 
	ptpt->ReturnX(); // 이렇게 접근 가능
	(*ptpt).ReturnY(); // 이렇게도 접근 가능

	Point** ptptpt = &ptpt; // 이중포인터...?
	// 주로 사용 위치는 2차원 객체 배열을 만들기 위해서 사용함
	// 단일포인터는 1차원을 표현하고 그 1차원들을 뭉친 이중 포인터로써 배열을 가지고 그 배열 안에 또 포인터 배열을 저장하는 방식.

	// 15. 다른 클래스 객체를 멤버로 가지는 경우
	// Array 안에 Point 멤버 객체를 가진다고 가정해볼까요
	// Array 안에 pt_로 Point 클래스 포함시킴

	// 16. friend 선언 + 17. static 멤버
	// 귀찮으니 한번에 같이
	
	EditXY(pt1, 0, 0); // 수정되고 ID까지 남음. ID는 더미로 남길 예정
	pt1.PrintXY();
	
	// 18. 복사 생성자
	// List class에 구현해두었음.

	// 19. 연산자 오버로딩 (산술 연산자, 전위 증감 연산자, 입출력 연산자, 대입 연산자)
	// 이거는 구현 귀찮아서 아래 예시만 끄적여놓을거임 (class Point 기준)
	// 산술 연산자 (+,-,*,/)
	//     얘는 그냥 Point& operator+(const Point& pt) 하고 밑에다가 함수 구현해주면 됨
	// 전위 증감 연산자 (++var, --var)
	//     Point& operator++(const Point& pt) 하고 역시 그냥 각 멤버에 대해 더하는 식으로 구현
	// 입출력 연산자
	// 얘는 ostream& operator<<(ostream& out, const Point& pt) 이런식으로 구현하면 되고
	// 마지막으로 대입연산자는 복사 생성자랑 내부 코드는 같은데
	// Point& operator=(const Point& pt) 로 시작하면 됨.
	// 얘네들 전부다 마지막에 return 넣는거 잊지말기. 결과값을 뱉던지, return out을 하던지. 케이스 보고 맞는 출력값 선정해서 출력하기

	// 2-1 중간고사 시험범위 한 코드에 때려넣기 끝
}
