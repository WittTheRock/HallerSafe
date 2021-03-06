// TestConsole.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../../PasswordGenerator.h"
#include <iostream>

int main()
{
	const int wordLength = 50;
	PasswordGenerator pg;

	pg.EnableNumbers(false);
	pg.EnableSpecialCharacters(false);

	for (int i = 0; i < 160; i++)
	{
		std::cout << pg.GenerateFriendlyPassword(wordLength).c_str() << std::endl;
	}

	getchar();
	return 0;
}

