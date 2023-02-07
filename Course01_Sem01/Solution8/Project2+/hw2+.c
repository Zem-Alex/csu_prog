#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//
void Output_A_Array(int* A_Array, int size_A);
void Output_B_Array(int* B_Array, int size_B);
void Definition_B_Array(int* B_Array, int size_B, int size_A, int* A_Array);
//
int main(void) {
    int size_A, size_B;
    //
    printf_s("Enter size of array A and B:\n");
    scanf_s("%d %d", &size_A, &size_B);
    //
    if (size_A > size_B) {
        int* A_Array = calloc(size_A, sizeof(int));
        for (int i = 0; i < size_A; ++i)
        {
            int sign = rand() % 2 ? 1 : -1;
            A_Array[i] = rand() % 21 + 10;
            A_Array[i] *= sign;
        }
        //
        Output_A_Array(A_Array, size_A);
        //
        printf_s("\n\nSize of array A: %d \n\n", size_A);
        //
        int* B_Array = calloc(size_B, sizeof(int));
        Definition_B_Array(B_Array, size_B, size_A, A_Array);
        //
        Output_B_Array(B_Array, size_B);
        //
        free(B_Array);
        free(A_Array);
        //
        return 0;
    }
    else
    {
        printf_s("Error! Enter value A > B");
        return 404;
    }
}

void Output_A_Array(int* A_Array, int size_A) {
    printf_s("\nArray A:\n");
    for (int i = 0; i < size_A; ++i) {
        printf_s("%d\t", A_Array[i]);
    }
}
void Output_B_Array(int* B_Array, int size_B) {
    printf_s("Array B:\n");
    for (int i = 0; i < size_B; ++i) {
        printf_s("%d\t", B_Array[i]);
    }
    printf_s("\n");
}
void Definition_B_Array(int* B_Array, int size_B, int size_A, int* A_Array) {
    int n = 0;
    for (int i = 0; i < size_B; ++i) {
        do {
            n = rand() % size_A;
            B_Array[i] = A_Array[n];  // [A_Array[0]; A_Array[size_A - 1]
            A_Array[n] = INT_MIN;
        } while (B_Array[i] == INT_MIN);
    }
}