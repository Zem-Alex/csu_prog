#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>

static enum CommandMask {
	MIN_LENGTH = 1, MAX_LENGTH = 2, LENGTH = 4,
	COUNT = 8, ALPHABET = 16, SPECIAL_ALPHABET = 32
};

static const char* LOWER_LATIN = "abcdefghijklmnopqrstuvwxyz";
static const char* UPPER_LATIN = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
static const char* DIGITS = "0123456789";
static const char* SPECIAL_SYMBOLS = ".,-_!@#$%^&*";

char* generatePassword(size_t minLength, size_t maxLength, char* alphabet) {
	size_t passwordLength = rand() % (maxLength - minLength + 1) + minLength + 1;
	char* password = malloc(passwordLength);
	size_t alphabetSize = strlen(alphabet);
	for (size_t i = 0; i < passwordLength - 1; i++) {
		size_t randomIndex = rand() % alphabetSize;
		password[i] = alphabet[randomIndex];
	}
	password[passwordLength - 1] = '\0';
	return password;
}

void printIncompatibilityMessage(const char* command1, const char* command2) {
	printf("Error: %s and %s are incompatible\n", command1, command2);
}

void printDuplicateMessage(const char* command) {
	printf("Error: Option %s repeats!\n", command);
}


bool checkArgument(size_t i, size_t size, const char* command) {
	if (i >= size || i < 0) {
		printf("Error: %s expects one more argument\n", command);
		return false;
	}
	return true;
}

/*
* функция для парсинга неотрицательного числа
* в случае сбоя выводится соответствующее сообщение и возвращается значение false
* успех - возврат true
*/
bool parseNonNegative(const char* toParse, size_t* Save, const char* command) {
	// парсим числа
	char* end = NULL;
	int base = 10;
	long value = strtol(toParse, &end, base);

	// проверка на корректность
	if (*end != '\0' || value < 0) {
		printf("Error: %s argument must be a non negative number\n", command);
		return false;
	}

	// обновим Save
	*Save = value;

	return true;
}

bool commandM1(const char* arg, int* commandsMask, size_t* minLength) {
	if (*commandsMask & MIN_LENGTH) {
		printDuplicateMessage("-m1");
		return false;
	}
	if (*commandsMask & LENGTH) {
		printIncompatibilityMessage("-m1", "-n");
		return false;
	}

	*commandsMask |= MIN_LENGTH;

	return parseNonNegative(arg, minLength, "-m1");
}

bool commandM2(const char* arg, int* commandsMask, size_t* maxLength) {
	if (*commandsMask & MAX_LENGTH) {
		printDuplicateMessage("-m2");
		return false;
	}
	if (*commandsMask & LENGTH) {
		printIncompatibilityMessage("-m2", "-n");
		return false;
	}

	*commandsMask |= MAX_LENGTH;

	return parseNonNegative(arg, maxLength, "-m2");
}

bool commandN(const char* arg, int* commandsMask, size_t* minLength, size_t* maxLength) {
	if (*commandsMask & MAX_LENGTH) {
		printIncompatibilityMessage("-n", "-m2");
		return false;
	}
	if (*commandsMask & MIN_LENGTH) {
		printIncompatibilityMessage("-n", "-m1");
		return false;
	}
	if (*commandsMask & LENGTH) {
		printDuplicateMessage("-n");
		return false;
	}

	*commandsMask |= LENGTH;

	if (!parseNonNegative(arg, minLength, "-n")) {
		return false;
	}
	*maxLength = *minLength;
	return true;
}

bool commandCount(const char* arg, int* commandsMask, size_t* count) {
	if (*commandsMask & COUNT) {
		printDuplicateMessage("-c");
		return false;
	}

	*commandsMask |= COUNT;

	return parseNonNegative(arg, count, "-c");
}

bool commandA(const char* arg, int* commandsMask, char** alphabet) {
	if (*commandsMask & ALPHABET) {
		printDuplicateMessage("-a");
		return false;
	}
	if (*commandsMask & SPECIAL_ALPHABET) {
		printIncompatibilityMessage("-a", "-C");
		return false;
	}

	*commandsMask |= ALPHABET;

	size_t alphabetSize = strlen(arg) + 1;
	*alphabet = malloc(alphabetSize);
	strcpy_s(*alphabet, alphabetSize, arg);
	return true;
}

bool commandC(const char* arg, int* commandsMask, char** alphabet) {
	if (*commandsMask & SPECIAL_ALPHABET) {
		printDuplicateMessage("-C");
		return false;
	}
	if (*commandsMask & ALPHABET) {
		printIncompatibilityMessage("-C", "-a");
		return false;
	}

	*commandsMask |= SPECIAL_ALPHABET;

	*alphabet = malloc(1);
	(*alphabet)[0] = '\0';
	size_t alphabetSize = 1;

	for (const char* option = arg; *option != '\0'; option++) {
		const char* symbolsToAdd = NULL;
		switch (*option) {
		case 'a':
			symbolsToAdd = LOWER_LATIN;
			break;
		case 'A':
			symbolsToAdd = UPPER_LATIN;
			break;
		case 'D':
			symbolsToAdd = DIGITS;
			break;
		case 'S':
			symbolsToAdd = SPECIAL_SYMBOLS;
			break;
		default:
			printf("Error: Unknown character %c in command -C\n", *option);
			return false;
		}

		alphabetSize += strlen(symbolsToAdd);
		char* tmp = realloc(*alphabet, alphabetSize);
		if (tmp == NULL) {
			printf("Error: Not enough memory\n");
			return false;
		}
		*alphabet = tmp;

		strcat_s(*alphabet, alphabetSize, symbolsToAdd);
	}

	return true;
}