#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ARRAY_HEIGHT 2
#define ARRAY_WIDTH 3
#define ERR_ALLOC_MEM "ERROR: couldn't allocate memory\nEXIT WITH ERROR CODE 1\n"

void Array_Declaration(int staticArr[ARRAY_HEIGHT][ARRAY_WIDTH]);
void Array_Output(int staticArr[ARRAY_HEIGHT][ARRAY_WIDTH]);
void Dynamic_Array_Output();

int main(void)
{
    int staticArr[ARRAY_HEIGHT][ARRAY_WIDTH];
    Array_Declaration(staticArr);
    Array_Output(staticArr);

    int size;
    printf_s("Enter an array size: ");
    scanf_s("%d", &size);

    int* iArray = calloc(size, sizeof(int));

    if (!iArray) {
        printf_s(ERR_ALLOC_MEM);
        return 1;
    }
    srand(time(NULL));
    for (int i = 0; i < size; ++i) {
        iArray[i] = rand() % (2 * size + 1) - size;  // [enter 10]
    }
    
    Dynamic_Array_Output(iArray, size);

    free(iArray);
	return 0;
}
void Array_Declaration(int staticArr[ARRAY_HEIGHT][ARRAY_WIDTH]) {
    for (int i = 0; i < ARRAY_HEIGHT; ++i) {
        for (int j = 0; j < ARRAY_WIDTH; ++j) {
            staticArr[i][j] = rand() % 101;
        }
    }
}
void Array_Output(int staticArr[ARRAY_HEIGHT][ARRAY_WIDTH]) {
    for (int i = 0; i < ARRAY_HEIGHT; ++i) {
        for (int j = 0; j < ARRAY_WIDTH; ++j) {
            printf_s("%d\t", staticArr[i][j]);
        }
        printf_s("\n");
    }
}
void Dynamic_Array_Output(int* iArray, int size) {
    for (int i = 0; i < size; ++i) {
        printf_s("%d ", iArray[i]);
    }
}