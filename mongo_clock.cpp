// 
// 
// 

#include "mongo_clock.h"

void MongoClock::DisplayTime(MD_MAXPanel *mp, time_t *time) {
	mp->clear();

	int normalizedHour = hour(*time) % 12;
	int lower = normalizedHour == 0 ? 0 : targets[normalizedHour - 1];
	int upper = targets[normalizedHour];
	int diff = upper - lower;
	int theTime = lower + (diff * (minute(*time) / 60.0));

	String timeString(theTime);
	int center = (mp->getXMax() / 2) - ((timeString.length() * 4) / 2);

	mp->drawText(center, mp->getYMax(), (char*)timeString.c_str(), MD_MAXPanel::ROT_0);
}