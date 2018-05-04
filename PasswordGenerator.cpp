#include "stdafx.h"
#include "PasswordGenerator.h"
#include <ctime>

const char LOWERCASE_CHARACTERS[] = "abcdefghijklmnopqrstuvwxyz";
const char UPPERCASE_CHARACTERS[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const char SPECIAL_CHARACTERS[] = "!#$&+?@";
const char NUMBERS[] = "1234567890";
const int NUMBER_OF_LOWERCASES = sizeof(LOWERCASE_CHARACTERS) / sizeof(LOWERCASE_CHARACTERS[0]);
const int NUMBER_OF_UPPERCASES = sizeof(UPPERCASE_CHARACTERS) / sizeof(UPPERCASE_CHARACTERS[0]);

PasswordGenerator::PasswordGenerator()
	: lowerCaseCharactersEnabled(true)
	, upperCaseCharactersEnabled(true)
	, specialCharactersEnabled(true)
	, numbersEnabled(true)
{
	srand(time(NULL));
}
PasswordGenerator::~PasswordGenerator()
{
}

void PasswordGenerator::EnableLowerCaseCharacters(bool enabled)
{
	this->lowerCaseCharactersEnabled = enabled;
}
void PasswordGenerator::EnableUpperCaseCharacters(bool enabled)
{
	this->upperCaseCharactersEnabled = enabled;
}
void PasswordGenerator::EnableSpecialCharacters(bool enabled)
{
	this->specialCharactersEnabled = enabled;
}
void PasswordGenerator::EnableNumbers(bool enabled)
{
	this->numbersEnabled = enabled;
}

string PasswordGenerator::GeneratePassword(int length) const
{
	if (!this->lowerCaseCharactersEnabled &&
		!this->upperCaseCharactersEnabled &&
		!this->specialCharactersEnabled &&
		!this->numbersEnabled)
		throw std::invalid_argument("no characters available for password generation.");

	string result;
	for (int index = 0; index < length; index++)
	{
		switch (rand() % 4)
		{
		case 0:
			if (this->numbersEnabled)
				result += NUMBERS[rand() % 10];
			else
				index--;

			break;
		case 1:
			if (this->lowerCaseCharactersEnabled)
				result += LOWERCASE_CHARACTERS[rand() % NUMBER_OF_LOWERCASES];
			else
				index--;

			break;
		case 2:
			if (this->upperCaseCharactersEnabled)
				result += UPPERCASE_CHARACTERS[rand() % NUMBER_OF_UPPERCASES];
			else
				index--;

			break;
		case 3:
			if (this->specialCharactersEnabled)
				result += SPECIAL_CHARACTERS[rand() % 7];
			else
				index--;

			break;
		default:
			break;
		}
	}

	return result;
}

string PasswordGenerator::GeneratePIN(int length) const
{
	string result;
	for (int index = 0; index < length; index++)
	{
		result += NUMBERS[rand() % 10];
	}

	return result;
}

char PasswordGenerator::GenerateChar(char start, char end) const
{
	char size = end - start + 1;
	char number = (char)(rand() % size);
	return start + number;
}
