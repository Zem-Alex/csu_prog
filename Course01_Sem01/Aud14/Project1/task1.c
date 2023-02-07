#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <malloc.h>

void RepeatSymbols(char* str, int length);

int main(int argc, char* argv[])
{
	int length = 0;
	length = strlen(argv[1]);

	RepeatSymbols(argv, length);

	return 0;
}
void RepeatSymbols(char* str, int length) {
	int count = 0, k = 0;

	for (char i = ' '; i <= '~'; i++)
	{
		count = 0;
		for (int j = 0; j < length; j++)
		{
			if (i == str[j])
				count++;
		}
		if (count > 1)
			k++;
	}
	printf_s("%d", k);
}

/*
void RepeatSymbols(char** argv, int length)
{
	int count = 0, k = 0;

	for (char i = ' '; i <= '~'; i++)
	{
		count = 0;
		for (int j = 0; j < length; j++)
		{
			if (i == argv[1][j])
				count++;
		}
		if (count > 1)
			k++;
	}
	printf_s("%d", k);
}*/