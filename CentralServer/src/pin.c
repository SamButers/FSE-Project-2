#include "pin.h"

int INPUT_PINS[INPUT_PINS_NUM];
int OUTPUT_PINS[OUTPUT_PINS_NUM];

int getPinFromIndex(int index) {
	switch(index) {
		case 0:
			return 6;
		case 1:
			return 25;
		case 2:
			return 21;
		case 3:
			return 22;
		case 4:
			return 26;
		case 5:
			return 27;
		case 6:
			return 28;
		case 7:
			return 29;
	}
	return -1;
}

int getIndexFromPin(int pin) {
	switch(pin) {
		case 6:
			return 0;
		case 25:
			return 1;
		case 21:
			return 2;
		case 22:
			return 3;
		case 26:
			return 4;
		case 27:
			return 5;
		case 28:
			return 6;
		case 29:
			return 7;
	}
	return -1;
}

void updatePin(int pin, int value) {
	INPUT_PINS[getIndexFromPin(pin)] = value;
}

void setInitialPins(unsigned char *pins) {
	for(int c = 0; c < INPUT_PINS_NUM; c++) {
		memcpy((void*) (INPUT_PINS + c), (void*) pins, 4);
		pins += 4;
	}
}