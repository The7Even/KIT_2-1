#include <iostream>
using namespace std;

int WrapperFunc(int val, int (*Func)(int))
{
	return Func(val);
}

int main()
{
	[](int x, int y) -> int { return x + y; };
	[](const char* msg) -> void {cout << msg << endl; };
	void (*PrintMsg)(const char*) = [](const char* msg) -> void {cout << msg << endl; };
	PrintMsg("Hello World.");

	int ary[5] = { 1,2,3,4,5 };
	for (int val : ary)
		cout << WrapperFunc(val, [](int a) -> int {return a * a; }) << endl;
}

// [](*함수이름)(매개변수) -> 반환자료형 { 함수 내용; }; <<< 람다함수의 구조
// [] 안에 그냥 변수이름만 넣으면 읽기만 가능. & 연산자 추가시 쓰기도 가능. = 연산자만 넣을시 외부 변수 읽기 가능, & 연산자만 넣을시 외부 변수에 쓰기 가능.
