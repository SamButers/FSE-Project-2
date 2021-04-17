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

void setIOInterruptions() {
	wiringPiISR(25, INT_EDGE_RISING, &pin25RisingInterruption);
	wiringPiISR(25, INT_EDGE_FALLING, &pin25FallingInterruption);
	
	wiringPiISR(26, INT_EDGE_RISING, &pin26RisingInterruption);
	wiringPiISR(26, INT_EDGE_FALLING, &pin26FallingInterruption);
	
	wiringPiISR(5, INT_EDGE_RISING, &pin05RisingInterruption);
	wiringPiISR(5, INT_EDGE_FALLING, &pin05FallingInterruption);
	
	wiringPiISR(6, INT_EDGE_RISING, &pin06RisingInterruption);
	wiringPiISR(6, INT_EDGE_FALLING, &pin06FallingInterruption);
	
	wiringPiISR(12, INT_EDGE_RISING, &pin12RisingInterruption);
	wiringPiISR(12, INT_EDGE_FALLING, &pin12FallingInterruption);
	
	wiringPiISR(16, INT_EDGE_RISING, &pin16RisingInterruption);
	wiringPiISR(16, INT_EDGE_FALLING, &pin16FallingInterruption);
	
	wiringPiISR(20, INT_EDGE_RISING, &pin20RisingInterruption);
	wiringPiISR(20, INT_EDGE_FALLING, &pin20FallingInterruption);
	
	wiringPiISR(21, INT_EDGE_RISING, &pin21RisingInterruption);
	wiringPiISR(21, INT_EDGE_FALLING, &pin21FallingInterruption);
}