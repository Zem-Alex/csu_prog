#include <iostream>

bool isSumEqualToThird(int a, int b, int c) 
{
        return a + b == c; // ¬ остальных случа€х выполн€ем обычное сравнение
}

int main() 
{
    int num1, num2, num3;

    std::cout << "Enter three nubers: ";
    std::cin >> num1 >> num2 >> num3;
    
    if (isSumEqualToThird(num1, num2, num3))
        std::cout << "True" << std::endl;
    else
        std::cout << "False" << std::endl;

    return 0;
}
