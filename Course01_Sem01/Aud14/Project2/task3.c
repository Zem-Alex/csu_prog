#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
    int N = 0, M = 0, k = 0;
    N = atoi(argv[1]);  M = atoi(argv[2]);
    k = (N * M) - 1;
    printf_s("%d", k);
}