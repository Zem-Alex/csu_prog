#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define size_M 10
#define size_N 5

int main(void)
{
    int arr[size_N][size_M], i = 0, j = 1, index = 0;
    do 
    {
        ++i;
        printf_s("%d\t", i * j);
        if ((i % size_M) == 0) 
        {
            printf_s("\n"); 
            index = index + i;
            i = 0;
            ++j;
        }
    } while (index < size_M * size_N);
    return 0;
}