#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int Larger_Number_Less_tan_N(int n, int sum, int count1, int x)
{
    int max = 0, count2 = 0;
    for (int i = 0; i < n; i++)
    {
        int sum2 = 0;
        x = i; count2 = 0;
        while (x)
        {
            count2++;
            sum2 = sum2 + x % 10;
            x = x / 10;
        }
        if ((sum == sum2) && ((n - i) % 9 == 0) && (count1 == count2))
        {

            int length = count1;
            char* arr = malloc(length * sizeof(char));
            _itoa_s(n, arr, length + 1, 10);

            for (int j = 0; j < length; ++j) {
                for (int i = 1; i < length; ++i) {
                    if (arr[i] < arr[i - 1]) {
                        // поменять элементы местами:
                        int tmp = arr[i];
                        arr[i] = arr[i - 1];
                        arr[i - 1] = tmp;
                    }
                }
            }
            char* arr2 = malloc(length * sizeof(char));
            _itoa_s(i, arr2, length + 1, 10);

            for (int j = 0; j < length; ++j) {
                for (int i = 1; i < length; ++i) {
                    if (arr2[i] < arr2[i - 1]) {
                        // поменять элементы местами:
                        int tmp = arr2[i];
                        arr2[i] = arr2[i - 1];
                        arr2[i - 1] = tmp;
                    }
                }
            }
            //printf_s("\n %d, %d, %s, %s \n", n, i, arr, arr2);
            if (atoi(arr) == atoi(arr2))
            {
                max = i;
            }

        }
    }
    printf_s("\n%d", max);
    return max;
}

int main(void)
{
    int x = 0, n = 0, max = 0, count1 = 0;
    int sum = 0;
    scanf_s("%d", &n);
    x = n;
    while (x) 
    {
        count1++;
        sum = sum + x % 10;
        x = x / 10;
    }
    
    Larger_Number_Less_tan_N(n, sum, count1, x);

}