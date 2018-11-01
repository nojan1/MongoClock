//
//
//

#include "button.h"

Button::Button(int pin)
{
	_pin = pin;

	pinMode(pin, INPUT_PULLUP);
}

const int Button::GetState()
{
	int pinState = digitalRead(_pin);

	if (firstTimeButtonPressed > 0 && verifiedTimeButtonPressed == 0)
	{
		if (pinState == LOW)
		{
			firstTimeButtonPressed = 0;
		}
		else if (millis() - firstTimeButtonPressed >= PRESSED_DURATION)
		{
			verifiedTimeButtonPressed = millis();
		}
	}
	else if (verifiedTimeButtonPressed > 0)
	{
		if (pinState == LOW)
		{
			firstTimeButtonPressed = 0;
			verifiedTimeButtonPressed = 0;

			if (millis() - verifiedTimeButtonPressed >= HELD_DURATION)
			{
				return KEY_HOLD;
			}
			else
			{
				return KEY_PRESS;
			}
		}
		else
		{
			if (millis() - verifiedTimeButtonPressed >= HELD_DURATION)
			{
				return KEY_HOLD;
			}
		}
	}
	else if (firstTimeButtonPressed == 0 && pinState == HIGH)
	{
		firstTimeButtonPressed = millis();
	}
	
	return KEY_UNDEFINED;
}
