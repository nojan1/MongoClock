// 
// 
// 

#include "button.h"

Button::Button(int pin) {
	_pin = pin;
	idleTimer = 0;

	pinMode(pin, INPUT_PULLUP);
}

const int Button::GetState() {
	if (digitalRead(_pin) == LOW) {
		if (firstTimeButtonPressed == 0) {
			firstTimeButtonPressed = millis();
		}
		else if (millis() - firstTimeButtonPressed >= HELD_DURATION) {
			firstTimeButtonPressed = 0;
			return KEY_PRESS;
		}
	}
	else {
		if (firstTimeButtonPressed > 0 && 
			millis() - firstTimeButtonPressed >= PRESSED_DURATION) {

			firstTimeButtonPressed = 0;
			return KEY_PRESS;
		}
		else {
			firstTimeButtonPressed = 0;
		}
	}

	return KEY_UNDEFINED;
}

