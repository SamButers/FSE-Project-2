#include "socket.h"
#include <stdio.h>

int clientSocket;
int serverSocket;
int incomingSocket;
pthread_t serverThread;

int initClient() {
	struct sockaddr_in serverAddress;
	
	if((clientSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
		return 1;
		
	memset(&serverAddress, 0, sizeof(serverAddress));
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_addr.s_addr = inet_addr(SERVER_IP);
	serverAddress.sin_port = htons(SERVER_PORT);
	
	if(connect(clientSocket, (struct sockaddr*) &serverAddress, sizeof(serverAddress)) < 0)
		return 2;
		
	int PIN_BYTES = (INPUT_PINS_NUM + OUTPUT_PINS_NUM) * 4;
	unsigned char *buffer = malloc(PIN_BYTES);
	getPinValues(buffer);
	
	if(send(clientSocket, buffer, PIN_BYTES, 0) != PIN_BYTES)
		return 3;
	
	printf("CLient: %d\n", clientSocket);
	
	return 0;
}

int initServer() {
	struct sockaddr_in serverAddress;
	struct sockaddr_in clientAddress;
	unsigned int clientSize;
	
	if((serverSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
		return 1;
		
	memset(&serverAddress, 0, sizeof(serverAddress));
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);
	serverAddress.sin_port = htons(PORT);
	
	if(bind(serverSocket, (struct sockaddr*) &serverAddress, sizeof(serverAddress)) < 0)
		return 2;
		
	if(listen(serverSocket, 10) < 0)
		return 3;
		
	clientSize = sizeof(clientAddress);
	if((incomingSocket = accept(serverSocket, (struct sockaddr*) &clientAddress, &clientSize)) < 0)
		return 4;
	
	pthread_create(&serverThread, NULL, &connectionHandler, NULL);
	return 0;
}

void sendPinUpdate(int pin, int value) {
	char buffer[8];
	
	memcpy((void*) buffer, (void*) &pin, 4);
	memcpy((void*) (buffer + 4), (void*) &value, 4);
	send(clientSocket, buffer, 8, 0);
	printf("Pin Update %d: %d\n", pin, value);
}

void* connectionHandler(void *args) {
	printf("Handler initialized\n");
	
	int receivedBytes;
	char buffer[8];
	
	int pin;
	int value;
	
	BMEData data;
	
	while((receivedBytes = recv(incomingSocket, buffer, 8, 0)) > 0) {
		if(receivedBytes == 4) {
			memcpy((void*) &pin, (void*) buffer, 4);
			
			togglePinValue(pin);
			value = getPinValue(pin);
			memcpy((void*) buffer, (void*) &value, 4);
			
			if(send(incomingSocket, buffer, 4, 0) != 4)
				printf("Send error\n");
		}
		
		else {
			getBMEData(&data);
			
			memcpy((void*) buffer, (void*) &(data.temperature), 4);
			memcpy((void*) (buffer + 4), (void*) &(data.humidity), 4);
			
			if(send(incomingSocket, buffer, 8, 0) != 8)
				printf("Send error\n");
		}
	}
	
	return NULL;
}

void joinClient() {
	close(clientSocket);
}

void joinServer() {
	pthread_cancel(serverThread);
	close(serverSocket);
	close(incomingSocket);
}

void testSocket() {
	char test = 'Y';
	send(clientSocket, &test, 1, 0);
}