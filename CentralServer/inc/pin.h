#ifndef PIN_H_
#define PIN_H_

#include <string.h>
#include "alarm.h"

#define INPUT_PINS_NUM 8
#define OUTPUT_PINS_NUM 6

extern int INPUT_PINS[INPUT_PINS_NUM];
extern int OUTPUT_PINS[OUTPUT_PINS_NUM];

int getInputPinFromIndex(int index);
int getInputIndexFromPin(int pin);
int getOutputPinFromIndex(int index);
int getOutputIndexFromPin(int pin);
void updatePin(int pin, int value);
void setInitialPins(unsigned char *pins);

#endif