#ifndef I2C_H_
#define I2C_H_
#include <stdint.h>
#include <unistd.h>
#include "bme280.h"

typedef struct BMEData {
	float temperature, humidity;
} BMEData;

void getBMEData(BMEData *data);

#endif