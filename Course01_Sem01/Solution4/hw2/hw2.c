#include <stdio.h> // ����������� ����/�����
#include <Windows.h> // ��� system()
#include <locale.h> // ��� setlocale()

int main(void) {
    setlocale(LC_ALL, "ru-RU"); // "����������" ������� �������
    int n;
    scanf_s("%d", &n);
    if (n % 2 == 0) {
        for (int i = 1; i <= n; i += 1) {
            printf_s("%d ", i);
        }
    }
    else {
        for (; n > 0; n -= 1) {
            printf_s("%d ", n);
        }
    }

        printf_s("\n");
        system("pause");
        return 0;
}