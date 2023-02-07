#include <stdio.h>
#include <stdlib.h>

#define maxArr 100

void inputArray(int arr[maxArr], int n, FILE* input);

int main(void) 
{
	FILE* input;
	if (fopen_s(&input, "new-keyboard.txt", "r") != 0) 
	{ 
		fclose(input);
	}
	fopen_s(&input, "new-keyboard.txt", "r");
	int n = 0, arr[maxArr], arr2[maxArr], count = 0, brokenkey = 0;
	fscanf_s(input, "%d ", &n);
	inputArray(arr, n, input);
	inputArray(arr2, maxArr, input);
	for (int i = 0; i < maxArr; ++i) 
	{
		if (arr2[i] > 0) 
		{
			count += 1;
		}
	}
	for (int i = 0; i < n; ++i) 
	{
		for (int j = 0; j < count; ++j) 
		{
			if (arr2[j] == i + 1) 
			{
				arr[i] -= 1;
			}
		}
		if (arr[i] < 0) 
		{
			brokenkey += 1;
		}
	}
	printf_s("%d\n", brokenkey);
	fclose(input);
	system("pause");
	return 0;
}
void inputArray(int arr[maxArr], int n, FILE* input) 
{
	for (int i = 0; i < n; ++i) 
	{
		fscanf_s(input, "%d", &arr[i]);
	}
}