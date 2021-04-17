#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "bme280.h"
#include "i2c.h"
#include "io.h"
#include "socket.h"

int bme280;

int initDevices() {
	int error;
	
	bme280 = bme280Init(1, 0x76);
	if(bme280) {
		printf("BME280 device initialization error.\n");
		return 1;
	}
	
	if(initIO()) {
		printf("I/O initialization error.\n");
		return 1;
	}
	
	if((error = initClient())) {
		printf("Client socket initialization error #%d\n", error);
		return 1;
	}
	
	return 0;
}

void joinDevices() {
	bme280Close();
	joinClient();
}

int main() {
	BMEData data;
	int IOPins[INPUT_PINS_NUM];
	
	if(initDevices())
		return 0;
	
	for(int c = 0; c < 5; c++) {
		getBMEData(&data);
		
		printf("Temperature: %f\n", data.temperature);
		printf("Humidity: %f\n\n", data.humidity);
		
		sleep(1);
	}
	
	getPinValues(IOPins);
	for(int c = 0; c < INPUT_PINS_NUM; c++)
		printf("PIN %d: %d\n", INPUT_PINS[c], IOPins[c]);
		
	setIOInterruptions();
	while(1)
		sleep(1);
	
	joinDevices();
	
	return 0;
}