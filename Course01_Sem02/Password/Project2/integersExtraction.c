#include <stdio.h>
#include <Windows.h>
#include <stdlib.h>
#include <conio.h>

FILE* file;

int main(void)
{
	printf_s("Tab + Enter to exit \n");
	int Size_Of_Line = 0, Count_Numbers = 0, number = 0, length_number = 0;
	char c = ' ';
	fopen_s(&file, "out.txt", "w");
	while (c != 9)
	{
		scanf_s("%c", &c, 1);
		fprintf_s(file, "%c", c);
		Size_Of_Line++;
	}
	//printf_s("Size_Of_Line = %i\n", Size_Of_Line);
	char* string = (char*)malloc(Size_Of_Line * sizeof(char));
	
	rewind(file);
	fclose(file);
	fopen_s(&file, "out.txt", "r");

	for (int i = 0; i < Size_Of_Line; i++)
	{
		fscanf_s(file, "%c", &string[i]);
	}
	
	printf_s("Finded ints^2 : ");
	number = atoi(string);
	if (number != 0)
	    printf_s("\n%i ", number * number);

	for (int i = 0; i < Size_Of_Line; i++)
	{
		if (string[i] >= '0' && string[i] <= '9')
	    {
			Count_Numbers++;
			length_number++;
			if (string[i + 1] >= '0' && string[i + 1] <= '9') 
			{
				Count_Numbers--;
				length_number++;
			}
			//printf_s("%c", string[i]);
		}
		else
		{
			if (string[i] == 9)
			{
				string[i] = '.';
			}
			else 
			{
				int j = i - length_number;
				for (j; j <= i; j++ )
				    string[j] = '0';
				number = atoi(string);
				if(number != 0)
				    printf_s("\n%i ", number * number);
				length_number = 0;
			}
		}
	}
	if (Count_Numbers == 0)
		printf_s("\nDone");
	//printf_s("\nFinded ints^2 : ");

	/*for (int i = 0; i < Count_Numbers; i++)
	{
		number = atoi(string);
		printf_s("\n%i ", number * number);
	}*/


	/*gets(string);
	for (int i = 0; i < Size_Of_Line; i++)
	{
		if (string[i] >= '0' && string[i] <= '9')
		{
            Count_Numbers++;
			printf_s("<_%c_>", string[i]);
		}
			
	}*/
	//printf_s("\nCount of Numbers: %i\n", Count_Numbers);
	
	
	fclose(file);
}