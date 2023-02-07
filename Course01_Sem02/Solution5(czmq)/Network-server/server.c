#include <zmq.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <Windows.h>

#pragma comment(lib,"libzmq-mt-sgd-4_3_4.lib")
#pragma comment(lib,"Ws2_32.lib")
#pragma comment(lib,"Iphlpapi.lib")

int main(void)
{
    //  Socket to talk to clients
    void* context = zmq_ctx_new();
    void* responder = zmq_socket(context, ZMQ_REP);
    int rc = zmq_bind(responder, "tcp://*:5555");
    int radix = 10;
    assert(rc == 0); // may be for any(thing) errors

    while (1) 
    {
        char buffer[21] = {'\0'};
        zmq_recv(responder, buffer, 21, 0);
        printf_s("Received '%s'\n", buffer);
        Sleep(1);          //  Do some 'work'

        char FirstStrNum[21] = { '\0' }, SecondStrNum[21] = { '\0' }, c = { '\0' };
        int FirstIntNum = 0, SecondIntNum = 0; int j = 0, result = 0;

        ParsingMessage(buffer, &FirstIntNum, &SecondIntNum, FirstStrNum, SecondStrNum, result, &c, j);

        result = MainOperation(result, FirstIntNum, SecondIntNum, c, &radix, responder);


        char resultStr[21]; int x = 0;

        _itoa_s(result, resultStr, 20, radix);
        
        zmq_send(responder, resultStr, 20, 0);

        radix = 10;
    }
    return 0;
}