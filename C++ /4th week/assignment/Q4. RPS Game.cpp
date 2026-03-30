#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int main()
{
	srand((unsigned int)time(NULL));

	int playerInput = 0;
	int comInput = 0;
	int winCount = 0; int loseCount = 0;
	for (int i = 0; i < 5; i++)
	{
		comInput = rand() % 3;
		cout << "가위(0), 바위(1), 보(2) 중 선택 >> ";
		cin >> playerInput;
		if (playerInput < 0 || playerInput > 2)
		{
			cout << "0,1, 또는 2만 입력하십시오." << endl;
			i--;
			continue;
		}
		// 가위바위보 승패여부 0 < 1 < 2 < 0 순서, 클수록 좋지만, 2는 0에게 패배.
		// 승패 판독에서 새로운 방법이 있었는데..
		// ((com + 1) % 3 == user)에서 True일경우 user 승, 같을경우는 무승부, 그 외에는 com 승. 밑의 조건보다 훨씬 간결함
		// if ((comInput + 1) % 3 == playerInput)으로 28번줄을 대체하여도 가능함. 대신 30,31번과 37,38번줄 맞바꾸어야함.
		if ((playerInput == 2 && comInput == 0) || (playerInput < comInput && playerInput != 2))
		{
			cout << "당신이 졌습니다." << endl;
			loseCount++;
		}
		else if (playerInput == comInput)
			cout << "비겼습니다." << endl;
		else
		{
			cout << "당신이 이겼습니다." << endl;
			winCount++;
		}
	}

	cout << "Human : Computer = " << winCount << " : " << loseCount << endl;
	if (winCount > loseCount)
		cout << "Human Wins";
	else if (winCount == loseCount)
		cout << "Draw";
	else
		cout << "Computer Wins";
}
