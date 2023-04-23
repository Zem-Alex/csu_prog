#pragma once


typedef char sequence_type;
typedef sequence_type* mass_sequence_type;

int NUMBER_SUBSTRINGS_IN_STRING(mass_sequence_type substr, mass_sequence_type str);

int STRLEN(mass_sequence_type substr);

mass_sequence_type REPLACING_IN_STRING(mass_sequence_type substr, mass_sequence_type str, mass_sequence_type newstr, int* backjoint, int* frontjoint, FILE* output);