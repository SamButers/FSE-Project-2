#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>
#include "bme280.h"
#include "i2c.h"
#include "io.h"
#include "socket.h"

int bme280;

int initDevices() {
	int error, attempts = 0;
	
	bme280 = bme280Init(1, 0x76);
	if(bme280) {
		printf("BME280 device initialization error.\n");
		return 1;
	}
	
	if(initIO()) {
		printf("I/O initialization error.\n");
		return 1;
	}
	
	setIOInterruptions();
	
	/*if((error = initServer())) {
		printf("Server socket initialization error #%d\n", strerror(error));
		printf("%s\n", strerror(errno));
		return 1;
	}*/
	
	while(1) {
		error = initClient();
		
		if(error)
			attempts++;
		else
			break;
		
		if(attempts >= 5) {
			printf("Client socket initialization error #%d\n", error);
			printf("%s\n", strerror(errno));
			return 1;
		}
		
		sleep(1);
	}
	
	return 0;
}

void joinDevices() {
	bme280Close();
	joinClient();
	joinServer();
}

void gracefullyStop(int sig) {	
	joinDevices();
	
	exit(0);
}

/*void mainLoop() {
	BMEData data;
	sigset_t sigSet;
	struct timespec waitTimeout = {0, 900000000};
	sigaddset(&sigSet, SIGALRM);
	
	while(1) {
		alarm(1);
		
		getBMEData(&data);
		sendBMEData(data.temperature, data.humidity);
		
		sigtimedwait(&sigSet, NULL, &waitTimeout);
	}
}*/

/**
Server will handle BME data sending and outpin setting.
Client will send pin updates.
**/
int main() {
	signal(SIGINT, gracefullyStop);
	
	if(initDevices())
		return 0;
	
	while(1)
		pause();
	
	return 0;
}