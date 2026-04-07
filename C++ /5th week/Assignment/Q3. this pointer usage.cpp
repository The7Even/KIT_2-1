#include <iostream>
using namespace std;

class Array {
public:
	int ary_[5];
	Array& Increase(int p) { ary_[p]++; return (*this); }
	int &GetItem(int i) { return ary_[i]; }
};

int main()
{
	int i;
	Array my_ary;

	for (i = 0; i < 5; i++) { my_ary.GetItem(i) = i; }

	my_ary.Increase(0).Increase(1).Increase(2).Increase(3).Increase(4);

	for (i = 0; i < 5; i++) { cout << "my_ary[" << i << "] " << my_ary.GetItem(i) << endl; }
}
