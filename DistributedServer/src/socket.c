#include "socket.h"
#include <stdio.h>

void initClient(int *socket) {
	*socket = -1;
}

int initServer() {
	return -1;
}

void sendPinUpdate(int pin, int value) {
	printf("Pin Update %d: %d\n", pin, value);
	return;
}