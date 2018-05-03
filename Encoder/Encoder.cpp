#include "Encoder.h"

#include <Arduino.h>
#include <stdio.h>
#include <inttypes.h>
#include <pins_arduino.h>


Encoder::Encoder(uint8_t pinA, uint8_t pinB, uint8_t pinSW) {
	this->pinA = pinA;
	this->pinB = pinB;
	this->pinSW = pinSW;
}

void Encoder::begin(uint8_t tickMultiply, uint16_t longPress) {
	this->buttonLastState = LOW;

	this->tickMultiply = tickMultiply;
	this->buttonLongPress = longPress;

	pinMode(this->pinA, INPUT);
	pinMode(this->pinB, INPUT);
	pinMode(this->pinSW, INPUT);
}

bool Encoder::update() {
	bool hasUpdate = false;

	// Check button
	uint8_t buttonCurrState = digitalRead(this->pinSW);

	if (this->isPressed()) {
		this->buttonPressed = false;
	}

	if (buttonCurrState != this->buttonLastState) {
		if (buttonCurrState == HIGH) {
			this->buttonDown = true;
			this->buttonPressed = false;
			this->buttonDownStart = millis();
		} else {
			this->buttonDown = false;
			this->buttonPressed = true;
			this->buttonDownStart = 0;
		}

		this->buttonLastState = buttonCurrState;

		hasUpdate = true;
	}

	// Check encoder
	uint8_t encoderCurrState = digitalRead(this->pinA);

	this->encoderDirection = ENCODER_DIR_NONE;

	if ((this->encoderLastState == LOW) && (encoderCurrState == HIGH)) {
		if (digitalRead(this->pinB) == LOW) {
			if (this->positionCurr > this->positionMin) {
				this->positionCurr--;
				this->encoderDirection = ENCODER_DIR_CLOCKWISE;
			}
		}
		hasUpdate = true;
	} else {
		if (this->positionCurr < this->positionMax) {
			this->positionCurr++;
			this->encoderDirection = ENCODER_DIR_COUNTERCLOCK;
		}
		hasUpdate = true;
	}

	this->encoderLastState = encoderCurrState;

	// Return update status
	return hasUpdate;
}

void Encoder::setMinMax(uint8_t min, uint8_t max) {
	this->positionMin = min;
	this->positionMax = max;
}

bool Encoder::isDown() {
	return this->buttonDown;
}

bool Encoder::isPressed() {
	return this->buttonPressed;
}

uint32_t Encoder::getDownTime() {
	return millis() - this->buttonDownStart;
}

uint8_t Encoder::getDirection() {
	return this->encoderDirection;
}

uint8_t Encoder::getPosition() {
	return this->positionCurr;
}

void Encoder::setPosition(uint8_t position) {
	this->positionCurr = position;
}

bool isLongPressed(bool reset){
	if(this->buttonDownStart + this->buttonLongPress < millis()){
		if(reset){
			this->buttonDownStart = millis();
		}
		return true;
	}
	
	return false;
}