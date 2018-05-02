#ifndef Menu_h
#define Menu_h

#include <stdio.h>
#include <string.h>
#include <inttypes.h>

class MenuItem {
private:
	string title = "";
	MenuItem[255] menuItems;
	uint8_t lastMenuIndex = 0;
	uint8_t itemIndex = 0;
public:
	MenuItem(string title, uint8_t index);
	
	addMenuItem(MenuItem item);
}

class Menu {
private:
	uint8_t lines = 3;
	uint8_t chars = 16;
	uint8_t menuIndex = 0;
	uint8_t itemIndex = 0;
	MenuItem[255] menuItems;
	uint8_t lastMenuIndex = 0;
public:
	Menu(uint8_t lines, uint8_t chars);
	
	addMenuItem(MenuItem item);
}
