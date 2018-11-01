#include <RtcDateTime.h>
#include <Wire.h>
#include <RtcDS3231.h>

#include "progress_clock.h"
#include "mongo_clock.h"
#include "normal_clock.h"
#include "clock_base.h"
#include <MD_MAX72xx.h>
#include <MD_MAXPanel.h>
#include "Font5x3.h"

#include "button.h"
#include "clock_base.h"

struct clock_list
{
	ClockBase *clock;
	clock_list *prev;
	clock_list *next;
};
typedef struct clock_list clock_list_t;

Button plusButton(7);
Button minusButton(6);

const MD_MAX72XX::moduleType_t HARDWARE_TYPE = MD_MAX72XX::FC16_HW;
const uint8_t X_DEVICES = 4;
const uint8_t Y_DEVICES = 1;

const uint8_t CLK_PIN = 13;  // or SCK
const uint8_t DATA_PIN = 11; // or MOSI
const uint8_t CS_PIN = 10;   // or SS

//MD_MAXPanel mp = MD_MAXPanel(HARDWARE_TYPE, DATA_PIN, CLK_PIN, CS_PIN, X_DEVICES, Y_DEVICES);
MD_MAXPanel mp = MD_MAXPanel(HARDWARE_TYPE, CS_PIN, X_DEVICES, Y_DEVICES);

clock_list_t *currentClock;
clock_list_t normalClock;
clock_list_t mongoClock;
clock_list_t progressClock;

bool timeSetMode = false;
unsigned long lastMillis = 0;

RtcDateTime last_datetime;
RtcDateTime datetime;
RtcDS3231<TwoWire> rtc(Wire);

void setup()
{
	Serial.begin(9600);

	setupClocks();
	mp.begin();

	rtc.Begin();
	datetime = rtc.GetDateTime();
}

void loop()
{
	if (!timeSetMode && millis() - lastMillis > 1000)
	{
		datetime = rtc.GetDateTime();
		lastMillis = millis();

		updateClock(false);
	}

	const int plusState = plusButton.GetState();
	const int minusState = minusButton.GetState();

	if (plusState == Button::KEY_HOLD && minusState == Button::KEY_HOLD)
	{
		if (timeSetMode)
		{
			rtc.SetDateTime(&datetime);
			delay(500);
		}

		timeSetMode = !timeSetMode;
	}
	else if (plusState != Button::KEY_UNDEFINED)
	{
		if (timeSetMode)
		{
			setTime(60);
		}
		else
		{
			currentClock = currentClock->next;
			updateClock(true);
		}
	}
	else if (minusState != Button::KEY_UNDEFINED)
	{
		if (timeSetMode)
		{
			setTime(-60);
		}
		else
		{
			currentClock = currentClock->prev;
			updateClock(true);
		}
	}
}

void setupClocks()
{
	normalClock.clock = new NormalClock();
	mongoClock.clock = new MongoClock();
	progressClock.clock = new ProgressClock();

	normalClock.next = &mongoClock;
	normalClock.prev = &progressClock;

	mongoClock.next = &progressClock;
	mongoClock.prev = &normalClock;

	progressClock.next = &normalClock;
	progressClock.prev = &mongoClock;

	currentClock = &normalClock;
}

void updateClock(bool force)
{
	if (force || datetime.Hour() != last_datetime.Hour() || datetime.Minute() != last_datetime.Minute())
		currentClock->clock->DisplayTime(&mp, &datetime);

	last_datetime = datetime;
}

void setTime(int amount)
{
	datetime += amount;
	updateClock(true);
}