#include <stdio.h> // ����������� ����/�����
#include <Windows.h> // ��� system()
#include <locale.h> // ��� setlocale()

int main(void) {
    setlocale(LC_ALL, "ru-RU"); // "����������" ������� �������

    int n;
    do {
        scanf_s("%d", &n);
        if (n == 0) {
            return 0; 
        }
        if (n % 2 == 0) {
            printf_s("׸����\n");
        }
        else {
            printf_s("��������\n");
        }

    } while (n != 0);

    printf_s("\n");
    system("pause");
    return 0;
}
