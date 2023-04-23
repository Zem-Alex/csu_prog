#pragma once

enum CommandMask {
	MIN_LENGTH = 1,
	MAX_LENGTH = 2, 
	LENGTH = 4,
	COUNT = 8, 
	ALPHABET = 16, 
	SPECIAL_ALPHABET = 32
};

const char* LOWER_LATIN = "abcdefghijklmnopqrstuvwxyz";
const char* UPPER_LATIN = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const char* DIGITS = "0123456789";
const char* SPECIAL_SYMBOLS = ".,-_!@#$%^&*";

char* generatePassword(size_t minLength, size_t maxLength, char* alphabet);