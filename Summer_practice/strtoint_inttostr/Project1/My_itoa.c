#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

int my_itoa(char* buf, int bufSize, int value, int sysnum)
{
	int tmp = value, numOfSymbols = 0, i, length, nullflag = 0, errbufSizeflag = 0; unsigned v = (unsigned)value;

	if (buf == NULL)
		nullflag = 1;

	//while (tmp)
	//{
	//	numOfSymbols++;
	//	tmp = tmp / 10;
	//}

	char str1[32] = {'\0'} /*= calloc(numOfSymbols, sizeof(char))*/, * str2 = str1;

	if (sysnum == 10 && value < 0)
		v = -value;

	while (v)
	{
		if (str2 - str1 > bufSize)
			errbufSizeflag = 1;
		i = v % sysnum;
		v /= sysnum;
		if (i < 10)
			*str2++ = i + '0';
		else if (i < 36)
			*str2++ = i + 'a' - 10;
		else
			*str2++ = i + 'A' - 36;
	}

	length = str2 - str1;

	if (sysnum == 10 && value < 0)
	{
		*buf++ = '-';
		length++;
	}

	while ((str2 > str1) && !nullflag && !errbufSizeflag)
		*buf++ = *--str2;

	if (errbufSizeflag)
		printf_s("\nIncorrect bufferSize!\n");
	if (nullflag) 
	{
		printf_s("\nBuf = NULL\n");
		return length;
	}
	return 1;
}