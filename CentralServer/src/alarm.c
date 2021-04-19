#include "alarm.h"

int ALARM = 0;

void toggleAlarm() {
	ALARM = !ALARM;
}

void soundAlarm() {
	system("omxplayer ../alarm.mp3");
	printf("Alarm sounded.\n");
}