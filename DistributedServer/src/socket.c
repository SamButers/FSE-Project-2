#include "socket.h"
#include <stdio.h>

int clientSocket;
int serverSocket;
int incomingSocket;
pthread_t serverThread;

int initClient() {
	struct sockaddr_in serverAddress;
	unsigned int messageSize;
	char buffer[] = "0";
	
	if((clientSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
		return 1;
		
	memset(&serverAddress, 0, sizeof(serverAddress));
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_addr.s_addr = inet_addr(SERVER_IP);
	serverAddress.sin_port = htons(SERVER_PORT);
	
	if(connect(clientSocket, (struct sockaddr*) &serverAddress, sizeof(serverAddress)) < 0)
		return 2;
		
	messageSize = strlen(buffer);
	if(send(clientSocket, buffer, messageSize, 0) != messageSize)
		return 3;
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
	
	int PIN_BYTES = INPUT_PINS_NUM * 4;
	unsigned char *buffer = malloc(PIN_BYTES);
	getPinValues(buffer);
	
	if(send(incomingSocket, buffer, PIN_BYTES, 0) != PIN_BYTES)
		return 5;
	
	free(buffer);
	
	pthread_create(&serverThread, NULL, &connectionHandler, NULL);
	return 0;
}

void sendPinUpdate(int pin, int value) {
	printf("Pin Update %d: %d\n", pin, value);
	return;
}

void* connectionHandler(void *args) {
	printf("Handler initialized\n");
	
	int receivedBytes;
	char buffer[8];
	
	int pin;
	int value;
	
	BMEData data;
	
	while((receivedBytes = recv(incomingSocket, buffer, 8, 0)) > 0) {
		if(receivedBytes == 8) {
			memcpy((void*) &pin, (void*) buffer, 4);
			memcpy((void*) &value, (void*) (buffer + 4), 4);
			
			setPinValue(pin, value);
			value = getPinValue(pin);
			memcpy((void*) buffer, (void*) value, 4);
			
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