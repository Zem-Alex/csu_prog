#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>
#include "Source.h"


int main(int argc, char* argv[]) {

	int commandsMask = 0;
	char* alphabet = NULL;
	size_t minLength = 5;
	size_t maxLength = 10;
	size_t count = 1;
	bool isCorrect = true;

	size_t i = 0;
	while (i < argc) {
		const char* command = argv[i];
		if (strcmp(command, "-m1") == 0) {
			i++;
			isCorrect = checkArgument(i, argc, "-m1") && commandM1(argv[i], &commandsMask, &minLength);
		}
		else if (strcmp(command, "-m2") == 0) {
			i++;
			isCorrect = checkArgument(i, argc, "-m2") && commandM2(argv[i], &commandsMask, &maxLength);
		}
		else if (strcmp(command, "-n") == 0) {
			i++;
			isCorrect = checkArgument(i, argc, "-n") && commandN(argv[i], &commandsMask, &minLength, &maxLength);
		}
		else if (strcmp(command, "-c") == 0) {
			i++;
			isCorrect = checkArgument(i, argc, "-c") && commandCount(argv[i], &commandsMask, &count);
		}
		else if (strcmp(command, "-a") == 0) {
			i++;
			isCorrect = checkArgument(i, argc, "-a") && commandA(argv[i], &commandsMask, &alphabet);
		}
		else if (strncmp(command, "-C", strlen("-C")) == 0) {
			// получаем параметры из команды
			size_t commandLength = strlen("-C");
			size_t optionLength = strlen(command) - commandLength + 1;
			char* options = malloc(optionLength);
			if (options == NULL) {
				printf("Error: Not enoguh memory\n");
				return 0;
			}
			strncpy_s(options, optionLength, command + commandLength, optionLength);

			// выполняем команду
			isCorrect = commandC(options, &commandsMask, &alphabet);

			// освобождаем память
			free(options);
		}
		if (!isCorrect) {
			free(alphabet);
			return 0;
		}
		i++;
	}

	// если алфавит не задан, устанавливаем значение по умолчанию
	if (alphabet == NULL) {
		size_t alphabetSize = strlen(LOWER_LATIN) + 1;
		alphabet = malloc(alphabetSize);
		if (alphabet == NULL) {
			printf("Error: Not enough memory\n");
			return 0;
		}
		strcpy_s(alphabet, alphabetSize, LOWER_LATIN);
	}

	// проверяет, что m1 и m2 либо оба существуют, либо нет
	if (commandsMask & MIN_LENGTH && !(commandsMask & MAX_LENGTH) || !(commandsMask & MIN_LENGTH) && commandsMask & MAX_LENGTH)
	{
		printf("Error: m1 and m2 must be set at the same time\n");
		free(alphabet);
		return 0;
	}

	// проверка длины minLength <= maxLength
	if (minLength > maxLength) {
		printf("Error: incorrect length, m1 argument must be less then m2 argument\n");
		free(alphabet);
		return 0;
	}

	// генерация пароля
	srand((unsigned)time(NULL));
	for (size_t i = 0; i < count; i++) {
		char* password = generatePassword(minLength, maxLength, alphabet);
		printf("%s\n", password);
		free(password);
	}

	// освобождаем память
	free(alphabet);

	return 0;
}