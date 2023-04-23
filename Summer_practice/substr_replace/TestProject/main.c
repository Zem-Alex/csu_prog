#include <stdio.h>
#include <stdlib.h>
#include "Func_With_Strings.h"

#define ERR_OPEN_FILE "ERROR: couldn't open a file\n"
#define ERR_NUM_ARGC "ERROR: incorrect number of entered arguments\n"
#define BUFFER_SIZE 512

int main(int argc, mass_sequence_type argv[])
{
	if (argc != 5) 
	{
		printf_s(ERR_NUM_ARGC);
		exit(1);
	}
    
	int countSymbols = 0, backjoint = 0, frontjoint = 0, flagcount = 0;;
	mass_sequence_type substr = argv[3],  newsubstr = argv[4],  newstr = 0, joint_mass = calloc(BUFFER_SIZE + STRLEN(argv[4]), sizeof(sequence_type));
    
	FILE* input, * output;
	if (fopen_s(&input, argv[1], "r") || fopen_s(&output, argv[2], "w"))
	{
		printf_s(ERR_OPEN_FILE);
		_fcloseall();
		exit(1);
	}
	while (!feof(input))
	{
		mass_sequence_type str = calloc(BUFFER_SIZE + 1, sizeof(sequence_type));
		countSymbols = fread(str, sizeof(sequence_type), BUFFER_SIZE, input);

		newstr = REPLACING_IN_STRING(substr, str, newsubstr, &backjoint, &frontjoint, output, joint_mass, &flagcount);

		countSymbols += NUMBER_SUBSTRINGS_IN_STRING(substr, str) * (STRLEN(newsubstr) - STRLEN(substr));
		free(str);
		if (frontjoint == 0)
		    fwrite(newstr + frontjoint, sizeof(sequence_type), countSymbols - backjoint, output);
		else
			fwrite(newstr, sizeof(sequence_type), countSymbols /*- frontjoint*/, output);
		flagcount = 0;
		
	}
	free(newstr);
	
	system("pause");
    
	return 0;
}