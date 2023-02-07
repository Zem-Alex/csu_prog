#include <stdio.h>
#include <stdlib.h>

#define MAX_ARRAY_SIZE 100
#define INPUT_FILE_NAME "numbers"
#define OUTPUT_FILE_NAME "sorted"
#define ERR_OPEN_FILE "ERROR: couldn't open a file\n"

void sort(int[MAX_ARRAY_SIZE], int numbersCount);

int main(void) 
{
    FILE* input, * output;
    int arr[MAX_ARRAY_SIZE], numbersCount = 0, count = 0;    
    if (fopen_s(&input, "numbers.txt", "r") || fopen_s(&output, "sorted.txt", "w")) 
    { 
        printf_s(ERR_OPEN_FILE);
        _fcloseall();
        exit(1);
    }
    while (fscanf_s(input, "%d ", &arr[count]) != EOF)
    {
        count += 1;
    }
    fclose(input);
    if (fopen_s(&input, "numbers.txt", "r") != 0)
    {
        fclose(input);
    }
   // fopen_s(&input, "numbers.txt", "r");
   //fopen_s(&output, "sorted.txt", "w");
    for (int i = 0; i < count; ++i)
    {
            fscanf_s(input, "%d ", &arr[i]);
    }     
        printf_s("\n ");
    sort(arr, count);
    for (int i = 0; i < count; ++i)
    {    
            fprintf_s(output, "%d ", arr[i]);
        
    }
    fclose(input);
    fclose(output);
    system("pause");
    return 0;
}

void sort(int arr[MAX_ARRAY_SIZE], int count) 
{
    for (int i = 0; i < count; ++i)
    {
        for (int j = 0; j < count - 1; ++j)
        {
            if (arr[j] > arr[j + 1])
            {
                int tmp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = tmp;
            }
        }
    }
}