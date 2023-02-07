#include <stdio.h> // стандартный ввод/вывод
#include <Windows.h> // для system()
#include <locale.h> // для setlocale()

int main(void) {
    setlocale(LC_ALL, "ru-RU"); // "подключает" русские символы
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