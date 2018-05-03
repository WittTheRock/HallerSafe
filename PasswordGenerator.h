#pragma once
#include <string>

using namespace std;

class PasswordGenerator
{
public:
	PasswordGenerator();
	~PasswordGenerator();

	void EnableLowerCaseCharacters(bool enabled);
	void EnableUpperCaseCharacters(bool enabled);
	void EnableSpecialCharacters(bool enabled);
	void EnableNumbers(bool enabled);

	string GeneratePassword(int length) const;
	string GeneratePIN(int length) const;

private:
	bool lowerCaseCharactersEnabled;
	bool upperCaseCharactersEnabled;
	bool specialCharactersEnabled;
	bool numbersEnabled;
};

