#ifndef Menu_h
#define Menu_h

#include <string.h>
#include <inttypes.h>

typedef void (* myFunctionPointer) ();

class MenuItem {
private:
	char title[16] = "";
	MenuItem menuItems[255];
	uint8_t itemIndex = 0;
	uint8_t lastMenuIndex = 0;
	myFunctionPointer functionPointer;
public:
	MenuItem(String title, myFunctionPointer functionPointer);
	
	void addMenuItem(MenuItem item);
};

class Menu {
private:
	uint8_t lines = 3;
	uint8_t chars = 16;
	uint8_t menuIndex = 0;
	uint8_t itemIndex = 0;
	MenuItem menuItems[255];
	uint8_t lastMenuIndex = 0;
public:
	Menu(uint8_t lines, uint8_t chars);
	void home();
	void addMenuItem(MenuItem item);
};
