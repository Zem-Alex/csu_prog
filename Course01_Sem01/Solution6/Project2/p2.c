#include <stdio.h> // стандартный ввод/вывод
#include <Windows.h> // для system()
#include <locale.h> // для setlocale()
#include <stdlib.h>

int main(void) {
    setlocale(LC_ALL, "ru-RU"); // "подключает" русские символы
    int arr[10];
    for (int i = 0; i < 10; ++i) {
        scanf_s("%d", &arr[i]);
    }
    printf_s("Array:\n");
    for (int i = 0; i < 10; ++i) {
        if (arr[i] > 0)
            printf_s("%d ", arr[i]);
    }

    return 0;
}