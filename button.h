// button.h

#ifndef _BUTTON_h
#define _BUTTON_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

#define PRESSED_DURATION 50
#define HELD_DURATION 100

class Button {
public:
	Button(int pin);
	const int GetState();

	static const int KEY_UNDEFINED = 0;
	static const int KEY_PRESS = 1;
	static const int KEY_HOLD = 2;
private:
	int _pin;
	unsigned long firstTimeButtonPressed = 0;
	unsigned long verifiedTimeButtonPressed = 0;
};

#endif

