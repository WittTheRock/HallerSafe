#include "Menu.h"

#include <Arduino.h>
#include <stdio.h>
#include <string.h>
#include <inttypes.h>

MenuItem::MenuItem(char title[16], myFunctionPointer functionPointer) {
	this->title = title;
	this->functionPointer = functionPointer
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

void Menu::home(){
	this->lastMenuIndex = 0;
	this->itemIndex = 0;
}

void Menu::addMenuItem(MenuItem item){
	this->menuItems[this->lastMenuIndex] = item;
	
	this->lastMenuIndex++;
}
