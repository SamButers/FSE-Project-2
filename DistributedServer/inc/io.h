#ifndef IO_H_
#define IO_H_

#include <wiringPi.h>

#define INPUT_PINS_NUM 8
#define OUTPUT_PINS_NUM 6

extern int INPUT_PINS[INPUT_PINS_NUM];
extern int OUTPUT_PINS[OUTPUT_PINS_NUM];

int initIO();
void joinIO();
void getPinValues(int *pins);

#endif