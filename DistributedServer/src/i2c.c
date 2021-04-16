#include "i2c.h"

void getBMEData(BMEData *data) {
	int temperature, pressure, humidity;
	
	usleep(100000);
	bme280ReadValues(&temperature, &pressure, &humidity);
	
	data->temperature = (float)temperature/100.0;
	data->humidity = (float)humidity/1000.0;
}