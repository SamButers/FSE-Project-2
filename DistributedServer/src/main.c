#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "bme280.h"
#include "i2c.h"

int main() {
	BMEData data;
	
	int bme280 = bme280Init(1, 0x76);
	if(bme280) {
		printf("BME280 device initialization error.\n");
		return 0;
	}
	
	for(int c = 0; c < 5; c++) {
		getBMEData(&data);
		
		printf("Temperature: %f\n", data.temperature);
		printf("Humidity: %f\n\n", data.humidity);
		
		sleep(1);
	}
	
	bme280Close();
	
	return 0;
}