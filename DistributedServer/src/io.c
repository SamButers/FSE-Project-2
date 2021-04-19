#include "io.h"

int INPUT_PINS[INPUT_PINS_NUM] = {21, 22, 26, 27, 28, 29, 6, 25};
int OUTPUT_PINS[OUTPUT_PINS_NUM] = {23, 0, 1, 24, 3, 2};

int initIO() {
	if(wiringPiSetup() == -1)
		return 1;
		
	for(int c = 0; c < INPUT_PINS_NUM; c++)
		pinMode(INPUT_PINS[c], INPUT);
		
	for(int c = 0; c < OUTPUT_PINS_NUM; c++)
		pinMode(OUTPUT_PINS[c], OUTPUT);
	
	return 0;
}

void getPinValues(unsigned char *buffer) {
	int value, c;
	
	for(c = 0; c < INPUT_PINS_NUM; c++) {
		value = digitalRead(INPUT_PINS[c]);
		memcpy((void*) buffer, &value, 4);
		buffer += 4;
		printf("Pin %d %d\n", INPUT_PINS[c], value);
	}
	
	for(c = 0; c < OUTPUT_PINS_NUM; c++) {
		value = digitalRead(OUTPUT_PINS[c]);
		memcpy((void*) buffer, &value, 4);
		buffer += 4;
		printf("Pin %d %d\n", OUTPUT_PINS[c], value);
	}
}

void setIOInterruptions() {
	wiringPiISR(6, INT_EDGE_BOTH, &pin25Interruption);
	wiringPiISR(25, INT_EDGE_BOTH, &pin26Interruption);
	wiringPiISR(21, INT_EDGE_BOTH, &pin05Interruption);
	wiringPiISR(22, INT_EDGE_BOTH, &pin06Interruption);
	wiringPiISR(26, INT_EDGE_BOTH, &pin12Interruption);
	wiringPiISR(27, INT_EDGE_BOTH, &pin16Interruption);
	wiringPiISR(28, INT_EDGE_BOTH, &pin20Interruption);
	wiringPiISR(29, INT_EDGE_BOTH, &pin21Interruption);
}

void togglePinValue(int pin) {
	int value = digitalRead(pin);
	digitalWrite(pin, !value);
}

int getPinValue(int pin) {
	return digitalRead(pin);
}