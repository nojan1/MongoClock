// 
// 
// 

#include "normal_clock.h"

void NormalClock::DisplayTime(MD_MAXPanel *mp, clocktime_t *time) {
	mp->clear();

	String hourString = String(time->hour, DEC);
	String minuteString = String(time->minute, DEC);
	String timeString = (time->hour < 10 ? "0" + hourString : hourString) + ":" + (time->minute < 10 ? "0" + minuteString : minuteString);

	int center = (mp->getXMax() / 2) - ((timeString.length() * 4) / 2);
	mp->drawText(center, mp->getYMax(), (char*)timeString.c_str(), MD_MAXPanel::ROT_0);
}