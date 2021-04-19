#ifndef PIN_H_
#define PIN_H_

#define INPUT_PINS_NUM 8
#define OUTPUT_PINS_NUM 6

typedef struct BMEData {
	float temperature, humidity;
} BMEData;

extern int INPUT_PINS[INPUT_PINS_NUM];
extern int OUTPUT_PINS[OUTPUT_PINS_NUM];

int getPinFromIndex(int index);
int getIndexFromPin(int pin);
void updatePin(int pin, int value);

#endif