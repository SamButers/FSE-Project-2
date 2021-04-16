#include "io.h"

int INPUT_PINS[INPUT_PINS_NUM] = {5, 6, 12, 16, 20, 21, 25, 26};
int OUTPUT_PINS[OUTPUT_PINS_NUM] = {13, 17, 18, 19, 22, 27};

int initIO() {
	if(wiringPiSetup() == -1)
		return 1;
		
	for(int c = 0; c < INPUT_PINS_NUM; c++)
		pinMode(INPUT_PINS[c], INPUT);
		
	for(int c = 0; c < OUTPUT_PINS_NUM; c++)
		pinMode(OUTPUT_PINS[c], OUTPUT);
	
	return 0;
}

void getPinValues(int *pins) {
	for(int c = 0; c < INPUT_PINS_NUM; c++)
		pins[c] = digitalRead(INPUT_PINS[c]);
}