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

// initialize the library with the numbers of the interface pins
DogLcd dspl(5, 6, 7, 8);

// initialize encoder with pins
Encoder encoderButton(2, 3, 4);

uint32_t eventLastMillis = 0;
uint32_t eventTimeoutMillis = 30000;

void setup() {
	// set up the LCD type and the contrast setting for the display 
	dspl.begin(DOG_LCD_M163);
	dspl.clear();
	
	if(isBatteryLow()){
		dspl.setCursor(0, 1);
		dspl.println("!!LOW BATTERY!!");
		delay(3000);
		dspl.clear();
	}
	
	Serial.begin(9600);
	encoderButton.begin(2, ENCODER_BTN_PULLUP); // clickMultiply not available yet
	encoderButton.setMinMax(0, 255);
	
	eventLastMillis = millis();
}

void loop() {
	dspl.setCursor(0, 0);
	dspl.print(millis()/1000);
	
	if(encoderButton.update()){
		eventLastMillis = millis();
	}
	
	if(eventLastMillis + eventTimeoutMillis < millis()){
		Serial.println('Sleep now...');
		//standBy();
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

bool isBatteryLow(){
	if(true == false){
		return true;
	}
	
	return false;
}

void standBy() {
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

void wakeUp() {
	// first thing after waking from sleep:
	// disable sleep...
	sleep_disable();

	// disables interrupt 0 on pin 2 so the
	// wakeUpNow code will not be executed
	// during normal running time.
	detachInterrupt(0);
	
	// Enable display
	dspl.display();
	
	// update event millis
	eventLastMillis = millis();
}