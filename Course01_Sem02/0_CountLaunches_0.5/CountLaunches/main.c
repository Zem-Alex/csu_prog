#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <locale.h>
#include <stdbool.h>

int n = 5;

int main() 
{
	setlocale(LC_ALL, "ru");
	HANDLE mt = CreateMutex(NULL, false, "CountLaunches.exe");
	if (GetLastError() == ERROR_ALREADY_EXISTS)
	{
		printf_s("\n��������� ��� ��������...\n\n");
		system("pause");
		return (0);
	}

	//HKEY R;
	//DWORD Value = 0;
	//DWORD cBuff;
	//char* path = TEXT("Count");
	//if (!RegCreateKeyEx(HKEY_CURRENT_USER, path, NULL, NULL, 0x00000001L, KEY_ALL_ACCESS, NULL, &R, NULL))
	//{
	//	if (RegQueryValueEx(R, path, NULL, NULL, &Value, &cBuff))
	//	{
	//		RegSetValueEx(R, path, NULL, REG_DWORD, &Value, 4); // '�������������'
	//	}
	//	else
	//	{
	//		Value++;

	//		if (Value > n)
	//		{
	//			printf_s("�� ��������� ��������� ����� %d ���\n\n��������� ���� �������� %d ���(a)\t������� ������ ����������!\n\n", n, Value);
	//			system("pause");
	//			exit(1);
	//		}
	//		else
	//			printf_s("��������� ���� �������� %d ���(�)\n", Value);

	//		RegSetValueEx(R, path, NULL, REG_DWORD, &Value, 4);
	//	}
	//}
	//
	//printf_s("\n������ ���������...\n\n");
	printf_s("\n������ ���������...\n\n");
	system("pause");
	return 0;
}

//ERROR_SUCCESS