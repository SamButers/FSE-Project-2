#include "pin.h"

int INPUT_PINS[INPUT_PINS_NUM];
int OUTPUT_PINS[OUTPUT_PINS_NUM];

int getInputPinFromIndex(int index) {
	switch(index) {
		case 0:
			return 21;
		case 1:
			return 22;
		case 2:
			return 26;
		case 3:
			return 27;
		case 4:
			return 28;
		case 5:
			return 29;
		case 6:
			return 6;
		case 7:
			return 25;
	}
	return -1;
}

int getInputIndexFromPin(int pin) {
	switch(pin) {
		case 21:
			return 0;
		case 22:
			return 1;
		case 26:
			return 2;
		case 27:
			return 3;
		case 28:
			return 4;
		case 29:
			return 5;
		case 6:
			return 6;
		case 25:
			return 7;
	}
	return -1;
}

int getOutputPinFromIndex(int index) {
	switch(index) {
		case 0:
			return 23;
		case 1:
			return 0;
		case 2:
			return 1;
		case 3:
			return 24;
		case 4:
			return 3;
		case 5:
			return 2;
	}
	return -1;
}

int getOutputIndexFromPin(int pin) {
	switch(pin) {
		case 23:
			return 0;
		case 0:
			return 1;
		case 1:
			return 2;
		case 24:
			return 3;
		case 3:
			return 4;
		case 2:
			return 5;
	}
	return -1;
}

void updatePin(int pin, int value) {
	INPUT_PINS[getInputIndexFromPin(pin)] = value;
	if(ALARM && value) {
		soundAlarm();
		registerAlarmEvent(pin);
	}
}

void setInitialPins(unsigned char *pins) {
	int c;
	
	for(c = 0; c < INPUT_PINS_NUM; c++) {
		memcpy((void*) (INPUT_PINS + c), (void*) pins, 4);
		pins += 4;
	}
	
	for(c = 0; c < OUTPUT_PINS_NUM; c++) {
		memcpy((void*) (OUTPUT_PINS + c), (void*) pins, 4);
		pins += 4;
	}
}