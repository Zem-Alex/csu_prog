#include <stdio.h>
#include <stdlib.h>

typedef char sequence_type;
typedef sequence_type* mass_sequence_type;

int NUMBER_SUBSTRINGS_IN_STRING(mass_sequence_type substr, mass_sequence_type str)
{
	int length_of_the_first_string = 0, length_of_the_second_string = 0, megacount = 0;

	length_of_the_first_string = STRLEN(str);
	length_of_the_second_string = STRLEN(substr);

	int j = 0, flag = 0, index = 0;
	for (int i = 0; i < length_of_the_first_string; i++)
	{
		index = i; flag = 0;
		if (substr[0] == str[index])
		{
			j = 0;
			for (index; index < length_of_the_second_string + i; index++)
			{
				if (substr[j] == str[index])
					j++;
				else
					break;
				flag = j;
			}
		}
		if (flag == length_of_the_second_string)
		{
			i += length_of_the_second_string - 1;
			megacount++;
		}
	}
	return megacount;
}

int STRLEN(mass_sequence_type substr)
{
	int i = 0;
	while (substr[i] != NULL)
		i++;
	return i;
}

char* REPLACING_IN_STRING(mass_sequence_type substr, mass_sequence_type str, mass_sequence_type newstr, int* backjoint, int* frontjoint, FILE* output, mass_sequence_type joint_mass, int* flagcount)
{
	int CountNumSubstrInStr = 0, length_of_the_first_string = 0, length_of_the_second_string = 0, length_of_the_third_string = 0, count = 0, i = 0, savei = 0, startpos = -111, endpos = -111;

	CountNumSubstrInStr = NUMBER_SUBSTRINGS_IN_STRING(substr, str);

	length_of_the_first_string = STRLEN(str);
	length_of_the_second_string = STRLEN(substr);
	length_of_the_third_string = STRLEN(newstr);

	int newlinesize = (length_of_the_first_string - (CountNumSubstrInStr * length_of_the_second_string) + (CountNumSubstrInStr * length_of_the_third_string));
	char* newline = (mass_sequence_type)calloc((newlinesize + 1), sizeof(char));

	int* IndexOfEnter = (int*)malloc(CountNumSubstrInStr * sizeof(int));

	int j = 0, jndex = 0, flag = 0, index = 0;

	if (*backjoint != 0)
	{
		for (int a = 0; a < length_of_the_first_string /*- *backjoint*/; a++)
		{
			if (str[a] != '\0')
			    joint_mass[a + *backjoint] = str[a];
		}



	    


		for (int i = 0, index = 0, j = 0; i < length_of_the_first_string; i++)
		{
			index = i; count = 0;
			if (substr[0] == joint_mass[index])
			{
				j = 0; startpos = index;
				for (index; index < length_of_the_second_string + i; index++)
				{
					if (substr[j] == joint_mass[index])
						j++;
					else
						break;
					count = j;
				}
			}
			if (count == length_of_the_second_string)
			{
				endpos = length_of_the_second_string + startpos;
				break;
			}
			else
			{
				(*backjoint)--;
			}
		}

		if (count == length_of_the_second_string)
		{
			fwrite(joint_mass, sizeof(sequence_type), startpos, output);
			fwrite(newstr, sizeof(sequence_type), length_of_the_third_string, output);
			*frontjoint = length_of_the_second_string - *backjoint; // length_of_the_second_string - *backjoint = count
			savei += length_of_the_second_string - *backjoint;
			*flagcount = length_of_the_third_string;
		}
		else
		{
			fwrite(joint_mass, sizeof(sequence_type), *backjoint, output);
			*frontjoint = 0;
			savei = 0;
		}







		/*for (int I = 0; I < length_of_the_second_string - *backjoint; I++)
		{
			if (str[I] == substr[I+ *backjoint])
				count++;
		}*/
		//if (count == length_of_the_second_string/* - *backjoint*/)
		//{
		//	fwrite(newstr, sizeof(sequence_type), length_of_the_third_string, output);
		//	*frontjoint = count; // length_of_the_second_string - *backjoint = count
		//	savei += count;
		//	*flagcount = length_of_the_third_string;
		//}
		//else
		//{
		//	fwrite(joint_mass, sizeof(sequence_type), *backjoint, output);
		//	*frontjoint = 0;
		//	savei = 0;
		//}
	}

	i = savei; *backjoint = 0;
	//
	for (i = savei; i < length_of_the_first_string; i++)
	{
		index = i; flag = 0;
		if (substr[0] == str[index])
		{
			j = 0;
			for (index; index < length_of_the_second_string + i; index++)
			{
				if (substr[j] == str[index])
					j++;
				else
				{
					if ((i + j) == (512) && *backjoint == 0) 
					{
						*backjoint = j;
						for (int a = 0; a < j; a++)
						{
							joint_mass[a] = str[i];
						}
						break;
					}
					break;
				}
				flag = j;
			}
		}
		if (flag == length_of_the_second_string)
		{
			IndexOfEnter[jndex] = i;
			i += (length_of_the_second_string - 1);
			jndex++;
		}

	}
	//
	jndex = 0;
	j = savei; 
	i = 0;

	while (i < newlinesize) 
	{
		if (j != IndexOfEnter[jndex])
		{
			newline[i] = str[j];
			j++; 
			i++;
		}
		else
		{
			j += length_of_the_second_string;
			for (int index_of_new_line = 0; index_of_new_line < length_of_the_third_string; index_of_new_line++, i++)
				newline[i] = newstr[index_of_new_line];
			jndex++;
		}
	}
	free(IndexOfEnter);

	return newline;
}