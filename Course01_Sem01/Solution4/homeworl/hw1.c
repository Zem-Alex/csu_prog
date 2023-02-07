#include <stdio.h> // стандартный ввод/вывод
#include <Windows.h> // для system()
#include <locale.h> // для setlocale()

int main(void) {
    setlocale(LC_ALL, "ru-RU"); // "подключает" русские символы
    int foo;
    scanf_s("%d", &foo);
    printf_s("foo = %d\n", foo);
    system("pause");
    return 0;
}