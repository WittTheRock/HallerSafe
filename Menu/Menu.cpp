#include "Menu.h"

#include <stdio.h>
#include <string.h>
#include <inttypes.h>

#if defined(ARDUINO) && (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif


MenuItem::MenuItem(string title) {
	this->title = title;
}

MenuItem::addMenuItem(MenuItem item){
	this->menuItems[this->lastMenuIndex] = item;
	
	this->lastMenuIndex++;
}

Menu::Menu(uint8_t lines, uint8_t chars) {
	this->lines = lines;
	this->chars = chars;
	
	MenuItem mainMenu("Main");
	
	this->addMenuItem(mainMenu);
}

Menu::addMenuItem(MenuItem item){
	this->menuItems[this->lastMenuIndex] = item;
	
	this->lastMenuIndex++;
}
