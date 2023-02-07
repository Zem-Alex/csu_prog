#pragma once

#include <zmq.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <Windows.h>

#pragma comment(lib,"libzmq-mt-sgd-4_3_4.lib")
#pragma comment(lib,"Ws2_32.lib")
#pragma comment(lib,"Iphlpapi.lib")

int MainOperation(int result, int FirstIntNum, int SecondIntNum, char c, int* radix, void* responder);
void ParsingMessage(char* buffer, int* FirstIntNum, int* SecondIntNum, char* FirstStrNum, char* SecondStrNum, int result, char* c, int j);