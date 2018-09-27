// 
// 
// 

#include "progress_clock.h"

void ProgressClock::DisplayTime(MD_MAXPanel *mp, clocktime_t *time) {
	mp->clear();

	int offsetX = (mp->getXMax() - 24) / 2;

	for (int i = 0; i < time->hour; i++) {
		mp->setPoint(offsetX + i, 6, true);
		mp->setPoint(offsetX + i, 5, true);
	}

	for (int i = 0; i < (time->minute / 2); i++) {
		mp->setPoint(i + 1, 2, true);
		mp->setPoint(i + 1, 1, true);
	}
}