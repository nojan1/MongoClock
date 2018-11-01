// normal_clock.h

#ifndef _NORMAL_CLOCK_h
#define _NORMAL_CLOCK_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "clock_base.h"

class NormalClock : public ClockBase {
public:
	void DisplayTime(MD_MAXPanel *mp, RtcDateTime *datetime);
};

#endif

