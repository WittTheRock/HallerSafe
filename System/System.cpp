#include "System.h"

#include <stdio.h>
#include <inttypes.h>
#include <avr/sleep.h>

#if defined(ARDUINO) && (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

System::System(uint8_t interruptId) {
	this->interruptId = interruptId;
}

void System::standBy() {
	// sleep mode is set here
	set_sleep_mode(SLEEP_MODE_PWR_DOWN);

	// enables the sleep bit in the mcucr register
	// so sleep is possible. just a safety pin
	sleep_enable();

	attachInterrupt(0, this->systemWakeUp, HIGH); // use interrupt 0 (pin 2) and run function

	/* 0, 1, or many lines of code here */
	//digitalWrite (pwr1, LOW);

	// here the device is actually put to sleep!!
	// THE PROGRAM CONTINUES FROM HERE AFTER WAKING UP
	sleep_mode();
}

void System::wakeUp() {
	// first thing after waking from sleep:
	// disable sleep...
	sleep_disable();

	// disables interrupt 0 on pin 2 so the
	// wakeUpNow code will not be executed
	// during normal running time.
	detachInterrupt(0);
}

char* System::getBattery(uint8_t type) {
	switch (type) {
		case BATTERY_VOLTAGE:
			return "3.2V";
			break;
		case BATTERY_PERCENTAGE:
			return "99%";
			break;
		default:
			return "NAN";
			break;
	}
}
