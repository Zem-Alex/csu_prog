#include <stdio.h>
#include <stdlib.h>
int main(void)
{
	int a, b;
	a = 5;
	copy(a, &b);
	return 0;
}
	void copy(int var1, int* var2) 
	{
		*var2 = var1;
	}
