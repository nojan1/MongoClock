// clock_base.h

#ifndef _CLOCK_BASE_h
#define _CLOCK_BASE_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include <RtcDateTime.h>
#include <MD_MAX72xx.h>
#include <MD_MAXPanel.h>

class ClockBase {
public:
	virtual void DisplayTime(MD_MAXPanel *mp, RtcDateTime *datetime) = 0;
};

#endif

