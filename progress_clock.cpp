// 
// 
// 

#include "progress_clock.h"

void ProgressClock::DisplayTime(MD_MAXPanel *mp, time_t *time) {
	mp->clear();

	int offsetX = (mp->getXMax() - 24) / 2;

	for (int i = 0; i < hour(*time); i++) {
		mp->setPoint(offsetX + i, 6, true);
		mp->setPoint(offsetX + i, 5, true);
	}

	for (int i = 0; i < (minute(*time) / 2); i++) {
		mp->setPoint(i + 1, 2, true);
		mp->setPoint(i + 1, 1, true);
	}
}