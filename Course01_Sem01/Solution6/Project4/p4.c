#include <stdio.h>
#include <stdlib.h>

#define ARRAY_SIZE 100

int main() {
    int arr[ARRAY_SIZE], arr2[ARRAY_SIZE], arr3[ARRAY_SIZE];
    int n;
    scanf_s("%d", &n);
    // заполнение массива случайными целыми числами из промежутка (-100, 100):
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        arr[i] = (rand() % 2 ? -1 : 1) * (rand() % 100);
    }
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        printf_s("%d ", arr[i]);
    } 
    printf_s("\nArray 2:\n");

    for (int i = 0; i < ARRAY_SIZE; ++i) {
        for (int i2 = 0; i2 < ARRAY_SIZE; ++i2) {
            for (int i3 = 0; i3 < ARRAY_SIZE; ++i3) {
                if (arr[i] % n == 0) {
                    arr[i2] = arr[i];
                }
                else {
                    arr[i3] = arr[i];
                }
            }
        }
    }

    system("pause");
    return 0;
}