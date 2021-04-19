#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include "socket.h"
#include "pin.h"

int initDevices() {
	int error, attempts = 0;

	/*while(1) {
		error = initClient();
		
		if(error)
			attempts++;
		else
			break;
		
		if(attempts >= 5) {
			printf("Client socket initialization error #%d\n", error);
			printf("%s\n", errno);
			return 1;
		}
		
		sleep(1);
	}*/
	
	if((error = initServer())) {
		printf("Server socket initialization error #%d\n", error);
		printf("%s\n", strerror(errno));
		return 1;
	}
	
	return 0;
}

void mainLoop() {
	while(1) {
		for(int c = 0; c < INPUT_PINS_NUM; c++)
			printf("Pin %d:%d\n", getPinFromIndex(c), INPUT_PINS[c]);
		printf("\n");
		sleep(1);
	}
}

int main() {
	if(initDevices())
		return 0;
	
	mainLoop();
	
	return 0;
}