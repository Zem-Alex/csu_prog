#include <stdio.h>
#include <stdlib.h>
int main(void) {
    int num1, num2, num3;
    FILE* input, * output;
    fopen_s(&input, "input.txt", "r");
    fopen_s(&output, "result.txt", "w");
    fscanf_s(input, "%d %d %d", &num1, &num2, &num3);
    int sum = check(num1, num2, num3);
    fprintf_s(output,"%d", sum); 
    fclose(input);
    fclose(output);
    return 0;
    }
int check(int var1, int var2, int var3) {
    if (var1 + var2 <= var3) 
    {
        return var3 - var1 - var2 + 1;
    }
    if (var1 + var3 <= var2)
    {
        return var2 - var1 - var3 + 1;
    }
    if (var3 + var2 <= var1)
    {
        return var1 - var3 - var2 + 1;
    }
    else
    {
        return 0;
    }
}