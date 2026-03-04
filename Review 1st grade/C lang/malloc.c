#include <stdio.h>
#include <stdlib.h>

int main(void)
{
  int* dummy = (int*)(sizeof(int)*4);
  free(dummy);
}
