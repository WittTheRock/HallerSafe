#ifndef Encoder_h
#define Encoder_h

#include <stdio.h>
#include <inttypes.h>

#define ENCODER_DIR_NONE 0
#define ENCODER_DIR_CLOCKWISE 1
#define ENCODER_DIR_COUNTERCLOCK 2
#define ENCODER_BTN_NORMAL 0
#define ENCODER_BTN_PULLUP 1

class Button {
private:
	/** The pin where the pin A is connected */
	uint8_t pinA = 0;
	/** The pin where the pin B is connected */
	uint8_t pinB = 0;
	/** The pin where the pin SW is connected */
	uint8_t pinSW = 0;

	/** Button down state */
	bool buttonDown = false;
	/** Button pressed state */
	bool buttonPressed = false;
	/** millis on button pressed down */
	uint32_t buttonDownStart = 0;
	/** Last state of button */
	uint8_t buttonLastState = LOW;

	/** Encoder position */
	uint8_t encoderDirection = ENCODER_DIR_NONE;
	/** Encoder last state */
	uint8_t encoderLastState = LOW;
	/** Encoder tick multiply */
	uint8_t tickMultiply = 1;

	/** Rotation current value */
	uint8_t positionCurr = 0;
	/** Rotation min value */
	uint8_t positionMin = 0;
	/** Rotation max value */
	uint8_t positionMax = 255;
public:
	/**
	 * Creates a new instance of Button.
	 * @param  pinA   The pin where pin A is connected.
	 * @param  pinB   The pin where pin B is connected.
	 * @param  pinSW  The pin where pin SW is connected.
	 * @return void
	 */
	Encoder(uint8_t pinA, uint8_t pinB, uint8_t pinSW);

	/** 
	 * Initializes the Encoder.
	 * @param  tickMultiply Define tick multiply (!!! Not implemented yet !!!).
	 * @param  pullup        Is internal pullup required.
	 * @return void
	 */
	void begin(uint8_t tickMultiply = 1, bool pullup = false);

	/**
	 * Update button states.
	 * @return bool
	 */
	bool update();

	/**
	 * Set min max position.
	 * @param  min  Min position (0-255)
	 * @param  max  Max position (0-255)
	 * @return void
	 */
	void setMinMax(uint8_t min, uint8_t max);

	/**
	 * Is button down.
	 * @return bool
	 */
	bool isDown();

	/**
	 * Is button pressed.
	 * @return bool
	 */
	bool isPressed();

	/**
	 * Get millis since button pressed down.
	 * @return uint32_t
	 */
	uint32_t getDownTime();

	/**
	 * Get encoder direction.
	 * @return uint8_t
	 */
	uint8_t getDirection();

	/**
	 * Get postion.
	 * @return uint8_t
	 */
	uint8_t getPosition();

	/**
	 * Set postion.
	 * @return void
	 */
	uint8_t setPosition(uint8_t position);

}

#endif