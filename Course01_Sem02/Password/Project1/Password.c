#include <stdio.h>
#include <Windows.h>
#include <stdlib.h>
#include <conio.h>

void CreateTable()
{
	char LeftTop = 201, LeftBottom = 200, RightTop = 187, RightBottom = 188;

	printf_s("Enter password(max 20 symbols):");
	printf_s("\n%c", LeftTop);
	for (int j = 0; j < 20; j++)
		printf_s("%c", 205);
	printf_s("%c\n%c", RightTop, 186);
	for (int j = 0; j < 20; j++)
		printf_s(" ");
	printf_s("%c\n", 186);
	printf_s("%c", LeftBottom);
	for (int j = 0; j < 20; j++)
		printf_s("%c", 205);
	printf_s("%c\n\f", RightBottom);

	COORD position = { 1,2 }; //позиция x и y
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsole, position);

}

int main(void)
{
	CreateTable();

	char* str[20] = {' '}, sbr[20] = {' '};
	char star = '*';
	int num = 0, let = 0, LET = 0, sym = 0;
	
	for (int i = 0; i < 20; i++)
	{
		
		str[i] = _getch();
		if (str[i] == 13)
		{
			sym = sym - (20 - i);
			break;
		}
			
		sbr[i] = str[i];
		if (str[i] != 8) 
		{
			str[i] = _putch(star);
		}
		if (str[i] == 8) {
			if (i <= 0)
			{
				i -= 1;
				continue;
			}
			else
			{
				str[i] = _putch('\b');
				str[i] = _putch(' ');
				str[i] = _putch('\b');
				sbr[i] = ' ';
				i -= 2;
			}
		}
		
	}
	printf_s("\n");
	printf_s("\nYour password: ");
	for (int i = 0; i < 20; i++)
	{
		if (sbr[i] != ' ')
		    printf_s("%c", sbr[i]);
		if (sbr[i] >= '0' && sbr[i] <= '9')
			num++;
		else
		{
			if (sbr[i] >= 'a' && sbr[i] <= 'z')
				let++;
			else
			{
				if (sbr[i] >= 'A' && sbr[i] <= 'Z')
					LET++;
				else
					if (sbr[i] != ' ')
				        sym++;
			}
		}
	}
	
	if (num < 3 || let < 3 || LET < 3 || sym < 3)
	    printf_s("\n Bad password! Numbers: %i Letters: %i BigLetters: %i OtherSymbols: %i", num , let, LET, sym);
	else 
		printf_s("\n Good password! Numbers: %i Letters: %i BigLetters: %i OtherSymbols: %i", num, let, LET, sym);
}