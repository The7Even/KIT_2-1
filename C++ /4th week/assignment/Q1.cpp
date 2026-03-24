#include <iostream>
using namespace std;

struct Circle
{
	int x;
	int y;
	int r;
};

int main()
{
	Circle cir1;

	while (1 > 0)
	{
		cout << "x,y 좌표와 반지름을 입력 (반지름을 음수로 입력하면 종료됩니다.)  >>> ";
		cin >> cir1.x >> cir1.y >> cir1.r;

		if (cir1.r < 0)
			break;

		cout << "좌표 (" << cir1.x << ", " << cir1.y << "), 반지름 : " << cir1.r << ", 면적 : " << cir1.r * cir1.r * 3.14 << endl;
	}
}
