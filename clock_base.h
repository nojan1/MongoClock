// clock_base.h

#ifndef _CLOCK_BASE_h
#define _CLOCK_BASE_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include <MD_MAX72xx.h>
#include <MD_MAXPanel.h>

typedef struct {
	uint8_t hour;
	uint8_t minute;
	uint16_t raw;
} clocktime_t;

class ClockBase {
public:
	virtual void DisplayTime(MD_MAXPanel *mp, clocktime_t *time) = 0;
};

#endif

