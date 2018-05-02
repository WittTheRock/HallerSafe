#ifndef System_h
#define System_h

#include <stdio.h>
#include <inttypes.h>
#include <avr/sleep.h>

#define BATTERY_PERCENTAGE 0
#define BATTERY_VOLTAGE 1

class System {
private:
	uint8_t interruptId = 0;
public:
	System();
	void standBy();
	void wakeUp();
	void eventTrigger();
	char* getBattery(uint8_t type);
}
