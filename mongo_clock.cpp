// 
// 
// 

#include "mongo_clock.h"

void MongoClock::DisplayTime(MD_MAXPanel *mp, RtcDateTime *datetime) {
	mp->clear();

	int normalizedHour = datetime->Hour() % 12;
	int lower = normalizedHour == 0 ? 0 : targets[normalizedHour - 1];
	int upper = targets[normalizedHour];
	int diff = upper - lower;
	int theTime = lower + (diff * (datetime->Minute() / 60.0));

	String timeString(theTime);
	int center = (mp->getXMax() / 2) - ((timeString.length() * 4) / 2);

	mp->drawText(center, mp->getYMax(), (char*)timeString.c_str(), MD_MAXPanel::ROT_0);
}