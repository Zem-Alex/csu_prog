#include <stdio.h> // ����������� ����/�����
#include <Windows.h> // ��� system()
#include <locale.h> // ��� setlocale()

int main(void) {
    setlocale(LC_ALL, "ru-RU"); // "����������" ������� �������
    int foo;
    scanf_s("%d", &foo);
    printf_s("foo = %d\n", foo);
    system("pause");
    return 0;
}