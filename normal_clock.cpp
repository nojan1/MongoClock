// 
// 
// 

#include "normal_clock.h"

void NormalClock::DisplayTime(MD_MAXPanel *mp, RtcDateTime *datetime) {
	mp->clear();

	String hourString = String(datetime->Hour(), DEC);
	String minuteString = String(datetime->Minute(), DEC);
	String timeString = (datetime->Hour() < 10 ? "0" + hourString : hourString) + ":" + (datetime->Minute() < 10 ? "0" + minuteString : minuteString);

	int center = (mp->getXMax() / 2) - ((timeString.length() * 4) / 2);
	mp->drawText(center, mp->getYMax(), (char*)timeString.c_str(), MD_MAXPanel::ROT_0);
}