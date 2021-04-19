#ifndef IO_H_
#define IO_H_

#include <wiringPi.h>
#include <string.h>
#include "interruptions.h"
#include <stdio.h>

#define INPUT_PINS_NUM 8
#define OUTPUT_PINS_NUM 6

extern int INPUT_PINS[INPUT_PINS_NUM];
extern int OUTPUT_PINS[OUTPUT_PINS_NUM];

int initIO();
void joinIO();
void getPinValues(unsigned char *buffer);
void setPinValue(int pin, int value);
int getPinValue(int pin);
void setIOInterruptions();

#endif