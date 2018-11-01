// 
// 
// 

#include "progress_clock.h"

void ProgressClock::DisplayTime(MD_MAXPanel *mp, RtcDateTime *datetime) {
	mp->clear();

	int offsetX = (mp->getXMax() - 24) / 2;

	for (int i = 0; i < datetime->Hour(); i++) {
		mp->setPoint(offsetX + i, 6, true);
		mp->setPoint(offsetX + i, 5, true);
	}

	for (int i = 0; i < (datetime->Minute() / 2); i++) {
		mp->setPoint(i + 1, 2, true);
		mp->setPoint(i + 1, 1, true);
	}
}