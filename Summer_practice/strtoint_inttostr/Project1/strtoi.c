#include <stdio.h>
#include <stdlib.h>

int STRLEN(char* substr)
{
	int i = 0;
	while (*(substr + i) != '\0')
		i++;
	return i;
}

int pow(int x, int n)
{
	if (n == 0)
		return 1;
	else if (n == 1)
		return x;
	else if (n % 2 == 0)
		return pow(x * x, n / 2);
	else
		return pow(x * x, n / 2) * x;
}

int strtoi(const char* str, char** p, int* ret)
{
	char max_str[34] = { '\0' };
	int k = STRLEN(str) - 1, i = 0, sign = 1, index = 0;
	int sos = 10;
	if (*str == 'b')
	{
		sos = 2;
		i++;
		k--;
	}
	else if (*str == '0' && *(str + 1) == 'x')
	{
		sos = 16;
		i += 2;
		k -= 2;
	}
	else if (*str == '0')
	{
		sos = 8;
		i++;
		k--;
	}



	for (i; *(str + i) != '\0'; i++)
	{
		if (sos == 2 && i > 0)
		{
			if (*(str + i) == '-' && i == 1)
			{
				i++;
				k--;
				sign *= -1;
			}
			if (*(str + i) == '0' || *(str + i) == '1')
			{
				*ret += (*(str + i) - '0') * pow(2, k);
			}
			else
			{
				*p = *(str + i);  //*p = str + i;
				return 0;
			}
		}
		else if (sos == 8 && i > 0)
		{
			if (*(str + i) == '-' && i == 1)
			{
				i++;
				k--;
				sign *= -1;
			}
			if (*(str + i) >= '0' && *(str + i) <= '7')
			{
				*ret += (*(str + i) - '0') * pow(8, k);
			}
			else
			{
				*p = *(str + i);  //*p = str + i;
				return 0;
			}
		}
		else if (sos == 16 && i > 1)
		{
			if (*(str + i) == '-' && i == 2)
			{
				i++;
				k--;
				sign *= -1;
			}
			if ((*(str + i) >= '0' && *(str + i) <= '9') || (*(str + i) >= 'A' && *(str + i) <= 'F'))
			{
				if (*(str + i) >= 'A' && *(str + i) <= 'F')
					*ret += (*(str + i) - 'A' + 10) * pow(16, k);
				else
					*ret += (*(str + i) - '0') * pow(16, k);
			}
			else
			{
				*p = *(str + i);  //*p = str + i;
				return 0;
			}
		}
		else if ((*(str + i) >= '0' && *(str + i) <= '9') || (* (str + i) == '-' && i == 0))
		{
			if (*(str + i) == '-' && i == 0)
			{
				i++;
				k--;
				sign *= -1;
			}
			*ret += (*(str + i) - '0') * pow(10, k);
		}
		else
		{
			*p = *(str + i);  //*p = *(str + i);
			return 0;
		}
		k--;
	}

	if (sos == 2)
	{
		if (sign == 1)
		{
			for (int j = 0; j < 32; j++)
			{
				*(max_str + j) = '1';//[31]
			}
		}
		else
		{
			index++;
			*max_str = '1';
			for (int j = 1; j < 33; j++)
			{
				*(max_str + j) = '0';//[31]
			}
		}
		for (int j = 2; *(str + j) != '\0'; j++)
		{
			if (*(str + j) == '0' && (j <= index + 1))
			{
				index++;
				continue;
			}
			if (STRLEN(str) - index - 1 < 32)
				break;
			if (STRLEN(str) - index - 1 > 32) 
			{
                printf_s("\nBuffer overflow\n");
			    return 0;
			}
				
			if (*(max_str + j - index ) == '\0')
			{
				printf_s("\nBuffer overflow\n");
				return 0;
			}
			if (*(str + j) > *(max_str + j - index - 1))
			{
				printf_s("\nBuffer overflow\n");
				return 0;
			}
		}
	}

	if (sos == 8)
	{
		if (sign == 1)
		{
			*max_str = '1';
			for (int j = 1; j < 11; j++)
			{
				*(max_str + j) = '7';
			}
		}
		else
		{
			*max_str = '2';
			for (int j = 1; j < 11; j++)
			{
				*(max_str + j) = '0';
			}
		}
		
		if (STRLEN(str) >= 12)
		{
			for (int j = 1; *(str + j) != '\0'; j++)
			{   
				if (*(str + j) == '0' && (j <= index+1) || (*(str + j) == '-'))
				{
					index++;
					continue;					
				}
				if (STRLEN(str) - index - 1 < 11)
					break;
				if (*(max_str + j - index - 1) == '\0')
				{
					printf_s("\nBuffer overflow\n");
					return 0;
				}
				if (*(str + j) < *(max_str + j - index - 1) && STRLEN(str) - index <= 12)
				{
					break;
				}
				if (*(str + j) > *(max_str + j - index - 1))
				{
					printf_s("\nBuffer overflow\n");
					return 0;
				}
			}
		}
	}

	if (sos == 16)
	{
		if (sign == 1)
		{
			*max_str = '7';
			for (int j = 1; j < 8; j++)
			{
				*(max_str + j) = 'F';
			}
		}
		else
		{
			*max_str = '8';
			for (int j = 1; j < 8; j++)
			{
				*(max_str + j) = '0';
			}
		}
		if (STRLEN(str) >= 10)
		{
			for (int j = 2; *(str + j) != '\0'; j++)
			{
				if (*(str + j) == '0' && (j <= index + 2) || *(str + j) == '-')
				{
					index++;
					continue;
				}
				if (STRLEN(str) - index < 10)
					break;
				if ((*(str + j) < *(max_str + j - index - 2)) && (STRLEN(str) - index <= 10))
					break;
				if (*(max_str + j - 2 - index) == '\0')
				{
					printf_s("\nBuffer overflow\n");
					return 0;
				}
				if (*(str + j) > *(max_str + j - 2 - index))
				{
					printf_s("\nBuffer overflow\n");
					return 0;
				}
			}
		}
	}
    
	if (sos == 10)
	{
		int flag = 0;
		char* max_int_str = "2147483647", * min_int_str = "2147483648";
		if (sign == -1)
		{
			max_int_str = min_int_str;

			if (STRLEN(str) >= 11)
			{
				for (int j = 0; *(str + j) != '\0'; j++)
				{
					if (*(str + j) == '0' && (j <= index) || *(str + j) == '-')
					{
						if (*(str + j) == '-' && j > 0)
						{
							*p = *(str + i);
							return 0;
						}
						index++;
						continue;
					}
					if (STRLEN(str) - index < 10)
						break;
					if ((*(str + j) < *(max_int_str + j - index)) && (STRLEN(str) - index <= 10))
						break;
					if (*(max_int_str + j - index) == '\0')
					{
						printf_s("\nBuffer overflow\n");
						return 0;
					}
					if (*(str + j) > *(max_int_str + j - index))
					{
						printf_s("\nBuffer overflow\n");
						return 0;
					}
				}
			}
		}
		else
		{
			if (STRLEN(str) >= 9)
			{
				for (int j = 0; *(str + j) != '\0'; j++)
				{
					if (*(str + j) == '0' && (j <= index) || *(str + j) == '-')
					{
						index++;
						continue;
					}
					if (STRLEN(str) - index < 10)
						break;
					if ((*(str + j) < *(max_int_str + j - index)) && (STRLEN(str) - index <= 10))
						break;
					if (*(max_int_str + j) == '\0')
					{
						printf_s("\nBuffer overflow\n");
						return 0;
					}
					if (*(str + j) > *(max_int_str + j))
					{
						printf_s("\nBuffer overflow\n");
						return 0;
					}
				}
			}
		}
	}

	*ret = *ret * sign;
	return 1;
}