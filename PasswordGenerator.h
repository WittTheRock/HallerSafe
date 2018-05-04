#pragma once
#include <string>

class PasswordGenerator
{
public:
	PasswordGenerator();
	~PasswordGenerator();

	void EnableLowerCaseCharacters(bool enabled);
	void EnableUpperCaseCharacters(bool enabled);
	void EnableSpecialCharacters(bool enabled);
	void EnableNumbers(bool enabled);

	std::string GeneratePassword(int length) const;
	std::string GenerateFriendlyPassword(int length) const;
	std::string GeneratePIN(int length) const;

private:
	char GenerateArbitraryLetter() const;
	char GenerateChar(char start, char end) const;
	std::string Knead(const std::string& pwd) const;
	bool IsAppropriateLetter(char ch, const std::string& pwd) const;
	bool IsConsonant(char ch) const;
	bool IsVowel(char ch) const;

private:
	bool lowerCaseCharactersEnabled;
	bool upperCaseCharactersEnabled;
	bool specialCharactersEnabled;
	bool numbersEnabled;
};
