#include <stdio.h> // ����������� ����/�����
#include <Windows.h> // ��� system()
#include <locale.h> // ��� setlocale()

int main(void) {
    setlocale(LC_ALL, "ru-RU"); // "����������" ������� �������
    int firstOperand , secondOperand , thirdOperand , fourthOperand , result1, result2;
    char operation;
    scanf_s("%d%d %c %d%d", &firstOperand, &secondOperand, &operation, 1, &thirdOperand, &fourthOperand);
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
    printf_s("(%d,%d)", result1, result2);

        return 0;
    }