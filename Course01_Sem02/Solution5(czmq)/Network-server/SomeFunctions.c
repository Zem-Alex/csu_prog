#include <zmq.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <Windows.h>

#pragma comment(lib,"libzmq-mt-sgd-4_3_4.lib")
#pragma comment(lib,"Ws2_32.lib")
#pragma comment(lib,"Iphlpapi.lib")



void ParsingMessage(char* buffer, int* FirstIntNum, int* SecondIntNum, char* FirstStrNum, char* SecondStrNum, int result, char* c, int j)
{
    printf_s("\n");
    for (size_t i = 0; i < 21; i++)
    {
        if (buffer[i] >= '0' && buffer[i] <= '9')
        {
            FirstStrNum[i] = buffer[i];
        }
        else
        {
            *c = buffer[i];
            j = i;
            break;
        }
    }

    int savej = j + 1;
    for (j; j < 21; j++)
    {
        if (buffer[j] >= '0' && buffer[j] <= '9')
        {
            SecondStrNum[j - savej] = buffer[j];
        }
        else
        {
            if (buffer[j - 1] == '-' && buffer[j] == '>')
            {
                *c = buffer[j];
                savej++;
                continue;
            }
        }
    }

    *FirstIntNum = atoi(FirstStrNum);

    *SecondIntNum = atoll(SecondStrNum);
}

int MainOperation(int result, int FirstIntNum, int SecondIntNum, char c, int* radix, void* responder)
{
    switch (c)
    {
    case '+':
        result = FirstIntNum + SecondIntNum;
        break;
    case '-':
        result = FirstIntNum - SecondIntNum;
        break;
    case '*':
        result = FirstIntNum * SecondIntNum;
        break;
    case '/':
        result = FirstIntNum / SecondIntNum;
        break;
    case '>':
        result = FirstIntNum;
        *radix = SecondIntNum;
        break;
    default:
        zmq_send(responder, "Unknown operation", 18, 0);
        exit(0);
    }
    return result;
}