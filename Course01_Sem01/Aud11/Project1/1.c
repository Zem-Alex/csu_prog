#include <stdio.h>
#include <stdlib.h>

#define ERR_ALLOC_MEM "ERROR: couldn't allocate memory\n EXIT WITH ERROR CODE 1"

int main(void) {
	int strSize = 0;
	strSize = (100 + 1) * sizeof(char);
	char* heapStr1 = malloc(strSize);
	char* heapStr2 = malloc(strSize);
	scanf_s("%s", heapStr1, strSize);
	scanf_s("%s", heapStr2, strSize);
	//printf_s("%s", heapStr1, strSize);
	//printf_s("%s", heapStr2, strSize);
	//printf_s("\n");
	int n, fact, sum = 1;
	n = atoi(heapStr1);
	//printf_s("n = %d", n);
	int size = 0, count = 0;
	size = strlen(heapStr2);
	//printf_s("\nsize = %d", size);
	for (int i = 0; i < size; ++i) {
		if (heapStr2[i] == '!') {
			count++;
		}
	}
	fact = count;
	//printf_s("\ncount = %d", count);
	for (int i = n; i > 0; i = i - fact){
		sum = sum * i;
	}
	printf_s("%d", sum);
	return 0;
}