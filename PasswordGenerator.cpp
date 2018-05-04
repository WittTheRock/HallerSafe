#include "stdafx.h"
#include "PasswordGenerator.h"
#include <random>
#include <ctime>

using namespace std;

const char SPECIAL_CHARACTERS[] = "!#$&+?@_-=~";
const int NUMBER_OF_SPECIAL = sizeof(SPECIAL_CHARACTERS) / sizeof(SPECIAL_CHARACTERS[0]) - 1;

PasswordGenerator::PasswordGenerator()
	: lowerCaseCharactersEnabled(true)
	, upperCaseCharactersEnabled(true)
	, specialCharactersEnabled(true)
	, numbersEnabled(true)
{
	srand((unsigned int)time(NULL));
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
				result += this->GenerateChar('0', '9');
			else
				index--;

			break;
		case 1:
			if (this->lowerCaseCharactersEnabled)
				result += this->GenerateChar('a', 'z');
			else
				index--;

			break;
		case 2:
			if (this->upperCaseCharactersEnabled)
				result += this->GenerateChar('A', 'Z');
			else
				index--;

			break;
		case 3:
			if (this->specialCharactersEnabled)
			{
				const int index = rand() % NUMBER_OF_SPECIAL;
				result += SPECIAL_CHARACTERS[index];
			}
			else
				index--;

			break;
		default:
			break;
		}
	}

	return result;
}
string PasswordGenerator::GenerateFriendlyPassword(int length) const
{
	string result;

	while (result.length() < (size_t)length)
	{
		char ch = this->GenerateArbitraryLetter();

		if (this->IsAppropriateLetter(ch, result))
			result += ch;
	}

	return this->Knead(result);
}
char PasswordGenerator::GenerateArbitraryLetter() const
{
	if (rand() % 2 == 0)
		return this->GenerateChar('a', 'z');

	return this->GenerateChar('A', 'Z');
}
string PasswordGenerator::Knead(const string& pwd) const
{
	string result;

	int doIt = 4;
	for (size_t index = 0; index < pwd.length(); index++)
	{
		char ch = pwd.at(index);

		if (index == 0 || (doIt >= 4 && this->IsConsonant(ch)))
		{
			result += toupper(ch);
			doIt = 0;
		}
		else
			result += tolower(ch);

		doIt++;
	}

	return result;
}
bool PasswordGenerator::IsAppropriateLetter(char ch, const string& pwd) const
{
	if (pwd.length() <= 0)
		return true;

	const char lastChar = pwd.at(pwd.length() - 1);
	if (!this->IsConsonant(lastChar))
		return true;

	if (!this->IsConsonant(ch))
		return true;

	return false;
}
bool PasswordGenerator::IsConsonant(char ch) const
{
	return !this->IsVowel(ch);
}
bool PasswordGenerator::IsVowel(char ch) const
{
	return (strchr("AEIOUaeiou", ch) != nullptr);
}

string PasswordGenerator::GeneratePIN(int length) const
{
	string result;
	for (int index = 0; index < length; index++)
	{
		result += this->GenerateChar('0', '9');
	}

	return result;
}

char PasswordGenerator::GenerateChar(char start, char end) const
{
	char size = end - start + 1;
	char number = (char)(rand() % size);
	return start + number;
}

