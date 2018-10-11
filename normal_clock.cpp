// 
// 
// 

#include "normal_clock.h"

void NormalClock::DisplayTime(MD_MAXPanel *mp, time_t *time) {
	mp->clear();

	String hourString = String(hour(*time), DEC);
	String minuteString = String(minute(*time), DEC);
	String timeString = (hour(*time) < 10 ? "0" + hourString : hourString) + ":" + (minute(*time) < 10 ? "0" + minuteString : minuteString);

	int center = (mp->getXMax() / 2) - ((timeString.length() * 4) / 2);
	mp->drawText(center, mp->getYMax(), (char*)timeString.c_str(), MD_MAXPanel::ROT_0);
}