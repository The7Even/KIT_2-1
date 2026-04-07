#include <iostream>
using namespace std;

class Stack {
private:
	int* data_;
	int len_; // 해당 코드에서는 5가 저장됨.
	int point_;
	bool maxed_;
public:
	// LIFO 알고리즘 기반 작동
	Stack(int amo) { 
		data_ = new int[amo]; 
		len_ = amo; 
		point_ = 0; 
		data_[0] = NULL; // 빈상태 표현용
		maxed_ = false;
	}

	bool IsEmpty() {
		return (data_[0] == NULL); // 스택의 0번 값이 NULL일 경우 빈 스택이라는 의미
	}

	void Push(int x) {
		if (maxed_ != true) { // 꽉차있지 않다면 값 삽입
			data_[point_] = x;
			if (point_ + 1 != len_) // point_가 4가 되는순간 false로 변경
			{
				data_[point_ + 1] = NULL;
				point_++;
			}
			else
				maxed_ = true;
		}
		else
			cout << "배열이 꽉 찼습니다!" << endl;
	}

	void PrintStack() {
		cout << "스택 요소 (old => new): ";
		int printPoint = 0;
		while (data_[printPoint] != NULL && printPoint < len_) // NULL을 만나거나 스택의 끝에 도달할때까지 반복.
//(기존에는 NULL 조건만 있었으나, 스택 범위를 벗어나도 쓰레기값이 가져와지고 NULL은 아니라 계속 불러와지는 오류가 발생함.)
		{
			cout << data_[printPoint] << " ";
			printPoint++;
		}
		cout << endl;
	}

	int Peek() { return data_[point_- 1]; }

	int Pop() {
		point_--;
		int temp = data_[point_];
		data_[point_] = NULL;
		maxed_ = false;
		return temp;
	}

	bool IsFull() { return maxed_; }
};

int main()
{
	Stack s(5);
	cout << "스택이 비어있나요? " << boolalpha << s.IsEmpty() << endl; // true

	s.Push(3);
	s.Push(10);
	s.Push(1);
	s.Push(7);
	s.PrintStack(); // 스택에 있는 모든 요소 출력 old => new

	cout << "현재 Top 데이터 : " << s.Peek() << endl; // 단순히 맨 위에 있는 요소 값 반환
	cout << "Top 데이터 꺼내기 : " << s.Pop() << endl; // 맨 위에 있는 요소 반환 후 제거
	cout << "Top 데이터 꺼내기 : " << s.Pop() << endl; // 맨 위에 있는 요소 반환 후 제거

	s.Push(5);
	s.Push(15);
	s.Push(6);

	s.PrintStack();
	cout << "스택이 가득 찼나요? " << s.IsFull() << endl; // true

}
