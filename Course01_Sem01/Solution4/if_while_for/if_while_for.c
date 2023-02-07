#include <stdio.h> // стандартный ввод/вывод
#include <Windows.h> // для system()
#include <locale.h> // для setlocale()

int main(void) {
    setlocale(LC_ALL, "ru-RU"); // "подключает" русские символы
    int floors;
    scanf_s("%d", &floors);
    printf_s("_\n");
    for (int i = 0; i <= floors; i += 1) {
        for (int j = 1; j < i + 2; j += 1) {
            printf_s(" ");
        }
            printf_s("|_\n ");
    }
    system("pause");
    return 0;
}
