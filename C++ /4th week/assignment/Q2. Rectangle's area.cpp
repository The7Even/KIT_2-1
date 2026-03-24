#include <iostream>
using namespace std;

struct Rect
{
	int x;
	int y;
};

int main()
{
	cout << "몇개의 사각형을 입력하시겠습니까? >> ";
	int amo=0;
	cin >> amo;

	Rect* RecList = new Rect[amo];
	for (int i = 0; i < amo; i++)
	{
		cout << i + 1 << "/" << amo << "번째 사각형의 가로, 세로 길이를 입력해 주세요 >> ";
		cin >> RecList[i].x >> RecList[i].y;

		if (RecList[i].x < 0 || RecList[i].y < 0)
		{
			cout << "유효한 값을 입력하여 주십시오." << endl;
			i--;
		}
	}

	for (int i = 0; i < amo; i++)
	{
		cout << i + 1 << "번째 사각형의 가로/세로 길이 : " << RecList[i].x << ", " << RecList[i].y << " // 면적 : " << RecList[i].x * RecList[i].y << endl;
	}

	delete RecList;
}
