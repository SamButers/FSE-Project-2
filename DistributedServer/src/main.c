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
	
	if((error = initServer())) {
		printf("Server socket initialization error #%d\n", error);
		printf("%s\n", strerror(errno));
		return 1;
	}
	
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
	
	setIOInterruptions();
	
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

int main() {
	signal(SIGINT, gracefullyStop);
	
	if(initDevices())
		return 0;
	
	while(1)
		pause();
	
	return 0;
}