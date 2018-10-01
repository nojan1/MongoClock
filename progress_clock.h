// progress_clock.h

#ifndef _PROGRESS_CLOCK_h
#define _PROGRESS_CLOCK_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "clock_base.h"

class ProgressClock : public ClockBase {
public:
	void DisplayTime(MD_MAXPanel *mp, RtcDateTime *datetime);
};

#endif

