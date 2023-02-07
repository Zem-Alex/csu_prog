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
    int rc = zmq_bind(responder, "tcp://*:5555"), user_num = 0;

    assert(rc == 0); // may be for any(thing) errors
    char buffer[21] = { '\0' };

    while (1)
    {
        zmq_recv(responder, buffer, 21, 0);
        user_num = atoi(buffer);
        printf_s("Received '%s'\n", buffer);
        Sleep(1);          //  Do some 'work'

        for (size_t i = 0; i < 20; i++)
        {
            scanf_s("%c", &buffer[i], 1);
            if (buffer[i] == '\n')
            {
                buffer[i] = '\0';
                break;
            }
        }

        zmq_send(responder, buffer, 20, 0);
    }
    return 0;
}