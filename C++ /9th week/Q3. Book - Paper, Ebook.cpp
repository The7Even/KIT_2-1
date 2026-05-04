#include <iostream>
#include <string.h>
using namespace std;

class Book {
protected:
	string title_;
	string author_;
	int price_;
public:
	Book(string t, string a, int p) : title_(t), author_(a), price_(p) {}
	void displayInfo() { cout << ">>> 도서명 : " << title_ << " | 저자 : " << author_ << " | 유형 : "; }
	int GetPrice() { return price_; }
};

class PaperBook : public Book {
protected:
	int weight_;
public:
	PaperBook(string t, string a, int p, int w) : Book(t,a,p), weight_(w) {}
	int GetPrice() { return Book::GetPrice() + weight_/2; }
	void displayInfo() { Book::displayInfo(); cout << "종이책 (무게 : " << weight_ << "g)" << endl; }
};

class Ebook : public Book {
protected:
	string format_;
public:
	Ebook(string t, string a, int p, string f) : Book(t,a,p), format_(f) {}
	int GetPrice() { return Book::GetPrice(); }
	void displayInfo() { Book::displayInfo(); cout << "전자책 (포맷 : " << format_ << ")" << endl; }
};

int main()
{
	cout << "=== 도서 관리 시스템 동작===" << endl;

	// 1. 종이책 생성 및 테스트
	PaperBook p1("C++ 프로그래밍", "황준하", 25000, 800);
	p1.displayInfo();
	cout << ">> 배송비 포함 결제 금액 : " << p1.GetPrice() << " 원" << endl;

	cout << "----------------------------------------------" << endl;

	// 2. 전자책 생성 및 테스트
	Ebook e1("파이썬 프로그래밍", "김코드", 18000, "pdf");
	e1.displayInfo();
	cout << ">> 결제 금액 : " << e1.GetPrice() << " 원" << endl;
}
