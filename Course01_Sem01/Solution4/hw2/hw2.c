#include <stdio.h> // стандартный ввод/вывод
#include <Windows.h> // для system()
#include <locale.h> // для setlocale()

int main(void) {
    setlocale(LC_ALL, "ru-RU"); // "подключает" русские символы
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