#include <stdio.h> // ����������� ����/�����
#include <Windows.h> // ��� system()
#include <locale.h> // ��� setlocale()

int main(void) {
    setlocale(LC_ALL, "ru-RU"); // "����������" ������� �������
    int N, i, sum;
    scanf_s("%d", &N);
    while (N > 0) {
        sum = 0; i = 0;
        while (sum + i <= N) {
             i = i + 1;
             sum = sum + i;
             printf_s("%d ", i);
        }
        printf_s("\n");
        N = N / 2;
    }

    printf_s("\n");
    system("pause");
    return 0;
}