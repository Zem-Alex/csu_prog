#include <stdio.h> // ����������� ����/�����
#include <Windows.h> // ��� system()
#include <locale.h> // ��� setlocale()
#include <stdlib.h>

int main(void) {
    setlocale(LC_ALL, "ru-RU"); // "����������" ������� �������
    int arr[10];
    for (int i = 0; i < 10; ++i) {
        scanf_s("%d", &arr[i]);
    }
    printf_s("Array:\n");
    for (int i = 0; i < 10; ++i) {
        if (arr[i] > 0)
            printf_s("%d ", arr[i]);
    }

    return 0;
}