#include <stdio.h>
#include <malloc.h>

void swap(int* a, int* b)
{
	int dum = 0;
	dum = *a;
	*a = *b;
	*b = dum;
}

int main(void)
{
	int a = 1;
	int b = 2;

	swap(&a, &b);

	printf("%d, %d", a, b);
}
