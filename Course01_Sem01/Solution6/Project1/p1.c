#include <stdio.h> // ����������� ����/�����
#include <Windows.h> // ��� system()
#include <locale.h> // ��� setlocale()
#include <stdlib.h>

int main(void) {
    setlocale(LC_ALL, "ru-RU"); // "����������" ������� �������
    int iArray[] = { 2, -7, 9, 43 };
    char chArray[] = { 'g', 'o', 'd', 'n', 'e', 's', 's' };

    for (int i = 0; i < 4; ++i) {
        printf_s("%d ", iArray[i]);
    }
    printf_s("\n");
    for (int i = 0; i < 7; ++i) {
        printf_s("%c ", chArray[i]);
    }

    return 0;
}