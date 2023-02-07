#include <stdio.h> // стандартный ввод/вывод
#include <Windows.h> // для system()
#include <locale.h> // для setlocale()

int main(void) {
    setlocale(LC_ALL, "ru-RU"); // "подключает" русские символы

    int a, b;
    scanf_s("%d%d", &a, &b);
    for (int i = 0; i <= a - 1; i++) {
        printf_s(" __   ");
    }

    for (int i = 0; i <= b - 1; i++) {
        printf_s("\n/  \\");
        for (int i = 0; i <= a - 2; i++) {
            printf_s("__/  \\");
        }
        printf_s("\n\\__/");
        for (int i = 0; i <= a - 2; i++) {
            printf_s("  \\__/");
        }

    }

    printf_s("\n");
    system("pause");
    return 0;
}


/*
#include <stdio.h> // стандартный ввод/вывод
#include <Windows.h> // для system()
#include <locale.h> // для setlocale()

int main(void) {
    setlocale(LC_ALL, "ru-RU"); // "подключает" русские символы

    int a, b;
    printf_s("%d%d", a, b);
    for (int i = 0; i <= 10; i++) {
        printf_s(" __   ");
    }

    for (int i = 0; i <= 4; i++) {
        printf_s("\n/  \\");
        for (int i = 0; i <= 9; i++) {
            printf_s("__/  \\");
        }
        printf_s("\n\\__/");
        for (int i = 0; i <= 9; i++) {
            printf_s("  \\__/");
        }

    }

    printf_s("\n");
    system("pause");
    return 0;
}
*/