#include <stdio.h> // стандартный ввод/вывод
#include <Windows.h> // для system()
#include <locale.h> // для setlocale()

int main(void) {
    setlocale(LC_ALL, "ru-RU"); // "подключает" русские символы
    int  b, c;
    char a; 
    scanf_s("%c",&a);
    scanf_s("%d%d", &b, &c);

    for (int i = 0; i < b; i += 1) {
        for (int j = 0; j < c; j += 1) {
            printf_s("%c ", a);
        }
        printf_s("\n");
    }

    printf_s("\n");
    system("pause");
    return 0;
}