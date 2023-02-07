#include <stdio.h> // стандартный ввод/вывод
#include <Windows.h> // для system()
#include <locale.h> // для setlocale()

int main(void) {
    setlocale(LC_ALL, "ru-RU"); // "подключает" русские символы
    float firstOperand, secondOperand, thirdOperand, fourthOperand;
    char operation, symbol;
    float result1, result2 = 0;
    scanf_s("%c%f%c%f%c %c %c%f%c%f%c", &symbol, 1, &firstOperand, &symbol, 1, &secondOperand, &symbol, 1, &operation, 1, &symbol, 1, &thirdOperand, &symbol, 1, &fourthOperand, &symbol, 1);
    switch (operation) {
    case '+':
        result1 = firstOperand + thirdOperand;
        result2 = secondOperand + fourthOperand;
        break;
    case '-':
        result1 = firstOperand - thirdOperand;
        result2 = secondOperand - fourthOperand;
        break;
    case '*':
        result1 = firstOperand * thirdOperand - secondOperand * fourthOperand;
        result2 = firstOperand * fourthOperand + secondOperand * thirdOperand;
        break;
    }
    printf_s("(%f;%f)", result1, result2);

    return 0;
}