/*
 * LCD SI pin to digital pin 2
 * LCD CLK pin to digital pin 3
 * LCD RS pin to digital pin 4
 * LCD CSB pin to digital pin 5
 * LCD RESET pin is not used
 * LCD Backlight pin is not used
 *
 * http://www.arduino.cc/en/Tutorial/LiquidCrystal
 /*
  
/*
 * Netbeans configuration
 * https://github.com/jaquesclaudino/arduino-netbeans/blob/master/doc/install.pdf
 */

// Include libraries
#include <Arduino.h>
#include <Serial.h>
#include <avr/sleep.h>
#include <EEPROM.h>

#include "DogLcd/DogLcd.h"
#include "Encoder/Encoder.h"
#include "Menu/Menu.h"

// Set defines
#define DEBUG_MODE // Enable debug mode 

#define batteryPin    A0 // Battery pin
#define batteryVolt    5 // Full voltage
#define warningVolt    2 // Warning voltage
#define warningTime 3000 // Warning message time

#define encoderPinSW         2 // Encoder SW
#define encoderPinA          4 // Encoder A
#define encoderPinB          3 // Encoder B
#define encoderTicks         2 // Encoder ticks
#define encoderLongPress  3000 // Encoder SW long press

#define displayPinSI  5 // LCD SI
#define displayPinCLK 6 // LCD CLK
#define displayPinRS  7 // LCD RS
#define displayPinCSB 8 // LCD CSB

// Set LCD chars
byte smiley1[8] = {
  B00000,
  B10001,
  B00000,
  B00000,
  B10001,
  B01110,
  B00000,
};
byte smiley2[8] = {
  B00000,
  B10001,
  B00000,
  B00000,
  B01110,
  B10001,
  B00000,
};
byte heart[8] = {
  B00000,
  B01010,
  B10101,
  B10001,
  B01010,
  B00100,
  B00000,
};

// Initialize the display
DogLcd dspl(displayPinSI, displayPinCLK, displayPinRS, displayPinCSB);

// Initialize encoder
Encoder encoderButton(encoderPinSW, encoderPinA, encoderPinA);

// Event timer
uint32_t eventLastMillis    =     0; // Last event millis
uint32_t eventTimeoutMillis = 30000; // Standby after millis

Menu mainMenu();

/**
 * Setup
 */
void setup() {
	#ifdef DEBUG_MODE
	Serial.begin(9600);
	#endif
	
	// Create LCD chars
	dspl.createChar(0, smiley1);
	dspl.createChar(1, smiley2);
	dspl.createChar(2, heart);
	
	// Set up the LCD type and the contrast setting for the display
	dspl.begin(DOG_LCD_M163, 0x3F, DOG_LCD_VCC_5V); // DOG_LCD_M163, 0, DOG_LCD_VCC_3V3
	dspl.clear();

	// Check battery
	if(isBatteryLow()){
		#ifdef DEBUG_MODE
		Serial.println("!!! BATTERY LOW !!!");
		#endif
		
		dspl.setCursor(0, 1);
		dspl.write(byte(1));
		dspl.setCursor(15, 1);
		dspl.write(byte(1));
		dspl.setCursor(2, 1);
		dspl.println("BATTERY LOW");
		delay(warningTime);
		dspl.clear();
	}
	
	// Set up encoder
	encoderButton.begin(encoderTicks, encoderLongPress); // tickMultiply not implemented yet
	encoderButton.setMinMax(0, 255);
	
	// Set menu
	MenuItem setting("Setting", null);
	setting.addMenuItem(new MenuItem("Master password", null));
	setting.addMenuItem(new MenuItem("Battery", null));
	mainMenu.addMenuItem(setting);
	
	eventLastMillis = millis();
}

/**
 * Loop
 */
void loop() {
	dspl.setCursor(0, 0);
	dspl.print(millis()/1000);
	
	if(encoderButton.update()){
		eventLastMillis = millis();
	}
	
	if(eventLastMillis + eventTimeoutMillis < millis()){
		#ifdef DEBUG_MODE
		Serial.println('Sleep now...');
		#endif
		
		//standBy();
	}
	
	if(encoderButton.isDown()){
		#ifdef DEBUG_MODE
		Serial.println("Down");
		#endif
	}else if(encoderButton.isPressed()){
		#ifdef DEBUG_MODE
		Serial.println("Pressed");
		#endif
	}
	
	if(encoderButton.isLongPressed()){
		#ifdef DEBUG_MODE
		Serial.print("Down since ");
		Serial.print(encoderLongPress/1000);
		Serial.println(" seconds");
		#endif
	}
	
	dspl.setCursor(0, 2);
	switch(encoderButton.getDirection()){
		case ENCODER_DIR_CLOCKWISE:
			dspl.print("--- UP --> ");
			break;
		case ENCODER_DIR_COUNTERCLOCK:
			dspl.print("<- DOWN -- ");
			break;
		default:
			dspl.print("-- NONE -- ");
			break;
	}
	
	dspl.print(encoderButton.getPosition());
	
	#ifdef DEBUG_MODE
	Serial.print("Position: ");
	Serial.println(encoderButton.getPosition());
	#endif
}

/**
 * Is battery low
 * http://www.instructables.com/id/Displaying-Battery-Life-on-a-Liquid-Crystal-Displa/
 * @return bool
 */
bool isBatteryLow(){
	float currVolt = (analogRead(batteryPin)/(1023/batteryVolt));
	
	if(currVolt <= warningVolt){
		return true;
	}
	
	return false;
}

/**
 * Standby
 */
void standBy() {
	#ifdef DEBUG_MODE
	Serial.println("Standby...");
	#endif
	
	// sleep mode is set here
	set_sleep_mode(SLEEP_MODE_PWR_DOWN);

	// enables the sleep bit in the mcucr register
	// so sleep is possible. just a safety pin
	sleep_enable();

	// use interrupt 0 (pin 2) and run function
	attachInterrupt(0, wakeUp, LOW); 
	
	dspl.reset();
	dspl.noDisplay();

	// here the device is actually put to sleep!!
	// THE PROGRAM CONTINUES FROM HERE AFTER WAKING UP
	sleep_mode();
}

/**
 * Wakeup
 */
void wakeUp() {
	// first thing after waking from sleep:
	// disable sleep...
	sleep_disable();
	
	#ifdef DEBUG_MODE
	Serial.println("WakeUp...");
	#endif
	
	// disables interrupt 0 on pin 2 so the
	// wakeUpNow code will not be executed
	// during normal running time.
	detachInterrupt(0);
	
	while(digitalRead(encoderPinSW) == HIGH){
		delay(10);
	}
	
	// Menu home 
	mainMenu.home();
	
	// Set encoder position
	encoderButton.setPosition(0);
	
	// Enable display
	dspl.display();
	
	// update event millis
	eventLastMillis = millis();
}