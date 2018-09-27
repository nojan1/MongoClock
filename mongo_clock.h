// mongo_block.h

#ifndef _MONGO_BLOCK_h
#define _MONGO_BLOCK_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "clock_base.h"

class MongoClock : public ClockBase {
public:
	void DisplayTime(MD_MAXPanel *mp, clocktime_t *time);
private:
	const int targets[13] = {1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4056};
};

#endif

