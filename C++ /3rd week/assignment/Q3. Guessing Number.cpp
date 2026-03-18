#include <iostream>
using namespace std;

void GuessNumber(int S, int M)
{
	string guess;
	cout << (S + M) / 2 << " is your Number? (input First letter of Bigger, Small, Right) >> ";
	cin >> guess;

	if (guess == "B")
		GuessNumber((S + M) / 2, M);
	if (guess == "S")
		GuessNumber(S, (S + M) / 2);
	if (guess == "R")
		cout << "Finished. Your Number is " << (S + M) / 2;
}

int main()
{
	int num;
	cout << "Choose Number (1~100)" << endl;
	GuessNumber(1, 100);
}
