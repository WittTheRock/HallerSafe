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
	string GenerateFriendlyPassword(int length) const;
	string GeneratePIN(int length) const;

private:
	char GenerateArbitraryLetter() const;
	char GenerateChar(char start, char end) const;
	string Knead(const string& pwd) const;
	bool IsAppropriateLetter(char ch, const string& pwd) const;
	bool IsConsonant(char ch) const;
	bool IsVowel(char ch) const;

private:
	bool lowerCaseCharactersEnabled;
	bool upperCaseCharactersEnabled;
	bool specialCharactersEnabled;
	bool numbersEnabled;
};
