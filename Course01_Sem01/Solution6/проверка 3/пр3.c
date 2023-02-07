#include <stdio.h> // стандартный ввод/вывод
#include <Windows.h> // для system()
#include <locale.h> // для setlocale()
#include <stdlib.h>

int main(void) {
    setlocale(LC_ALL, "ru-RU"); // "подключает" русские символы
    int arr[10], arr2[5], max, n, swap;
    for (int i = 0; i < 10; ++i) {
        scanf_s("%d", &arr[i]);
    }

    printf_s("\n");
    for (int j = 0; j < 5; ++j) {
        n = 0;
        for (int i = 0; i < 10; ++i) {
            max = arr[0];
            if (arr[i] > max) {
                max = arr[i];
                n = i;
            }
        } 
        arr2[j] = arr[n];
        arr[n] = arr[0];
        
        printf_s("%d ", arr2[j]);
    }
    printf_s("\n");
    for (int i = 0; i < 5; ++i) {
        for (int j = 1; j < 5; ++j) {
            if (arr2[j] < arr2[j - 1]) {
                swap = arr2[j];
                arr2[j] = arr2[j - 1];
                arr2[j - 1] = swap;
            }
        }
    }
    for (int j = 0; j < 5; ++j) {
        printf_s("%d ", arr2[j]);
    }
    return 0;
}