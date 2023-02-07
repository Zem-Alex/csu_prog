#include <stdio.h> // стандартный ввод/вывод
#include <Windows.h> // для system()
#include <locale.h> // для setlocale()
#include <stdlib.h>

int main(void) {
	int arr1[10], arr2[5];
	for (int i = 0; i < 10; ++i)
		scanf_s("%d", &arr1[i]);
	for (int j = 0; j < 10; ++j) {
		for (int i = 1; i < 10; ++i) {
			if (arr1[i] < arr1[i - 1]) {
				int swap = arr1[i];
				arr1[i] = arr1[i - 1];
				arr1[i - 1] = swap;
			}
		}
	}
	for (int i = 0; i < 5; ++i) {
		arr2[i] = arr1[i + 5];
		printf_s("%d ", arr2[i]);
	}
	return 0;
}