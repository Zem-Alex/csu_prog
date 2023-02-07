#include <stdio.h> // стандартный ввод/вывод
#include <Windows.h> // для system()
#include <locale.h> // для setlocale()

int main(void) {
    setlocale(LC_ALL, "ru-RU"); // "подключает" русские символы

    int n;
    do {
        scanf_s("%d", &n);
        if (n == 0) {
            return 0; 
        }
        if (n % 2 == 0) {
            printf_s("Чётное\n");
        }
        else {
            printf_s("Нечётное\n");
        }

    } while (n != 0);

    printf_s("\n");
    system("pause");
    return 0;
}
