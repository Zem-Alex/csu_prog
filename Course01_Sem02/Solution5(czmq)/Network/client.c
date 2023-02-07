#include <zmq.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <Windows.h>

#pragma comment(lib,"libzmq-mt-s-4_3_4.lib")
#pragma comment(lib,"Ws2_32.lib")
#pragma comment(lib,"Iphlpapi.lib")

int main(void)
{
    printf("Connecting to server...\nAvailable operations: a + b, a - b, a * b , a / b , a -> b\nEnter the expression(20 symbols - max):\n>");
    void* context = zmq_ctx_new();
    void* requester = zmq_socket(context, ZMQ_REQ);
    zmq_connect(requester, "tcp://localhost:5555");

    int request_nbr;
    for (request_nbr = 0; request_nbr < 10; request_nbr++) 
    {
        char buffer[21], message[21] = { '\0' };
        for (size_t i = 0; i < 20; i++)
        {
            scanf_s("%c", &message[i], 1);
            if (message[i] == '\n')
            {
                message[i] = '\0';
                break;
            }
                
        }
        printf_s("Sending '%s' (%d)\n", message, request_nbr);
        zmq_send(requester, message, 20, 0); // в примере было 5
        zmq_recv(requester, buffer, 21, 0);
        printf("Received '%s' (%d)\n", buffer, request_nbr);
    }
    zmq_close(requester);
    zmq_ctx_destroy(context);
    return 0;
}