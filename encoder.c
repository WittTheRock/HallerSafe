/*
 * LCD SI pin to digital pin 2
 * LCD CLK pin to digital pin 3
 * LCD RS pin to digital pin 4
 * LCD CSB pin to digital pin 5
 * LCD RESET pin is not used
 * LCD Backlight pin is not used
 *
 * http://www.arduino.cc/en/Tutorial/LiquidCrystal
 */

// include the library code:
#include <DogLcd.h>
#include <Serial.h>
#include <Encoder.h>

Encoder encoderButton(2, 3, 4);

uint32_t eventLastMillis = 0;
uint32_t eventTimeoutMillis = 30000;

// initialize the library with the numbers of the interface pins
DogLcd dspl(5, 6, 7, 8);

void setup() {
	// set up the LCD type and the contrast setting for the display 
	dspl.begin(DOG_LCD_M163);
	// Print a message to the LCD.
	dspl.print("hello, world!");
	
	Serial.begin(9600);
	encoderButton.begin(2, ENCODER_BTN_PULLUP); // clickMultiply not available yet
	encoderButton.setMinMax(0, 255);
	
	eventLastMillis = millis();
}

void loop() {
	// set the cursor to column 0, line 1
	// (note: line 1 is the second row, since counting begins with 0):
	dspl.setCursor(0, 0);
	// print the number of seconds since reset:
	dspl.print(millis()/1000);
	
	// SW:
	if(encoderButton.update()){
		eventLastMillis = millis();
	}
	
	if(eventLastMillis + eventTimeoutMillis < millis()){
		Serial.println('Sleep now...');
		//standBy()
	}
	
	if(encoderButton.isDown()){
		Serial.println("Down");
	}else if(encoderButton.isPressed()){
		Serial.println("Pressed");
	}
	
	if(encoderButton.getDownTime() % 15000 == 0){
		Serial.println("Down since 15 seconds");
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
	
	lcd.print(encoderButton.getPosition());
}

void batteryCheck(uint8_t type){
	
}

void standBy() {
	// sleep mode is set here
	set_sleep_mode(SLEEP_MODE_PWR_DOWN);

	// enables the sleep bit in the mcucr register
	// so sleep is possible. just a safety pin
	sleep_enable();

	attachInterrupt(0, this->systemWakeUp, HIGH); // use interrupt 0 (pin 2) and run function

	/* 0, 1, or many lines of code here */
	dspl. (pwr1, LOW);

	// here the device is actually put to sleep!!
	// THE PROGRAM CONTINUES FROM HERE AFTER WAKING UP
	sleep_mode();
}

void wakeUp() {
	// first thing after waking from sleep:
	// disable sleep...
	sleep_disable();

	// disables interrupt 0 on pin 2 so the
	// wakeUpNow code will not be executed
	// during normal running time.
	detachInterrupt(0);
	
	eventLastMillis = millis();
}