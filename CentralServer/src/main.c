#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "socket.h"

int main() {
	initServer();
	
	while(1) {
		sleep(1);
	}
	
	return 0;
}