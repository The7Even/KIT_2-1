#include <iostream>
using namespace std;

class ClassA
{
public:
	ClassA() { cout << "ClassA::ClassA()" << endl; }
	ClassA(int n) { cout << "ClassA::ClassA(" << n << ")" << endl; }
};

class ClassB
{
public:
	ClassB() { cout << "ClassB::ClassB()" << endl; }
	ClassB(int n) : obj_a1(n)
	{
		ClassA temp_a(-n);
		ClassB temp_b;
		cout << "ClassB::ClassB(" << n << ")" << endl;
	}
private:
	ClassA obj_a1;
	ClassA obj_a2;
};

int main()
{
		ClassB obj_b(3);
}

// 실제 출력값과 그에 대한 분석
// ClassA::ClassA(3) >> obj_a1(n)에서 나온 결과
// ClassA::ClassA() >> obj_a2가 마저 생성됨
// ClassA::ClassA(-3) >> temp_a 결과물
// ClassA::ClassA() >> temp_b의 결과로 classA가 2개 생성됨
// ClassA::ClassA() >> 굳이 따지자면 얘는 temp_b.obj_a2
// ClassA::ClassB() >> temp_b의 결과로 생성된 classB의 생성자
// ClassA::ClassB(-3) >> 마지막 main에서의 생성자 출력
