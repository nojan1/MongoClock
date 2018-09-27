
#include "progress_clock.h"
#include "mongo_clock.h"
#include "normal_clock.h"
#include "clock_base.h"
#include <MD_MAX72xx.h>
#include <MD_MAXPanel.h>
#include "Font5x3.h"

#include "button.h"
#include "clock_base.h"

struct clock_list {
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

const uint8_t CLK_PIN = 13;   // or SCK
const uint8_t DATA_PIN = 11;  // or MOSI
const uint8_t CS_PIN = 10;    // or SS

//MD_MAXPanel mp = MD_MAXPanel(HARDWARE_TYPE, DATA_PIN, CLK_PIN, CS_PIN, X_DEVICES, Y_DEVICES);
MD_MAXPanel mp = MD_MAXPanel(HARDWARE_TYPE, CS_PIN, X_DEVICES, Y_DEVICES);

clock_list_t *currentClock;
clock_list_t normalClock;
clock_list_t mongoClock;
clock_list_t progressClock;

clocktime_t lastClockTime;

bool timeSetMode = false;
unsigned long time = 9*3600ul + 30*60 + 57;
unsigned long lastMillis = 0;

void setup()
{
	Serial.begin(9600);

	setupClocks();
	mp.begin();
}

void loop()
{
	if (millis() - lastMillis > 1000) {
		time += (millis() - lastMillis) / 1000;
		lastMillis = millis();

		updateClock(false);
	}

	const int plusState = plusButton.GetState();
	const int minusState = minusButton.GetState();

	if (plusState == Button::KEY_HOLD && minusState == Button::KEY_HOLD) {
		timeSetMode = !timeSetMode;
	}
	else if (plusState != Button::KEY_UNDEFINED) {
		if (timeSetMode) {
			//Not implemented
		}
		else {
			Serial.write("Pressed plus");
			currentClock = currentClock->next;
			updateClock(true);
		}
	}
	else if (minusState != Button::KEY_UNDEFINED) {
		if (timeSetMode) {
			//Not implemented
		}
		else {
			currentClock = currentClock->prev;
			updateClock(true);
		}
	}
}

void setupClocks() {
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

void updateClock(bool force) {
	clocktime_t clockTime;
	clockTime.raw = time;
	clockTime.hour = time / 3600;
	clockTime.minute = (time % 3600) / 60;

	if(force || clockTime.hour != lastClockTime.hour || clockTime.minute != lastClockTime.minute)
		currentClock->clock->DisplayTime(&mp, &clockTime);

	lastClockTime = clockTime;
}