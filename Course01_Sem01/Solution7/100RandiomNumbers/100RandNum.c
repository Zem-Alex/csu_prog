#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include<locale.h>


int main()
{
	setlocale(LC_ALL, "ru-RU");
	srand((unsigned int)time(0));
	FILE* output;
	int i = 0, count = 100;
	if (fopen_s(&output, "C:\\\\Users\\79507\\Desktop\\Папки\\Программирование\\C\\Solution7\\Project1\\numbers.txt", "a") == 0)
	{
		while (i < count)
		{
			fprintf_s(output, "%d ", rand() % 100);
			++i;
		}
		fclose(output);
	}
	return 0;
}