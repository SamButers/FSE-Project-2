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
		
	unsigned char *buffer = malloc(INPUT_PINS_NUM * 4);
	getPinValues(buffer);
	
	send(incomingSocket, buffer, INPUT_PINS_NUM * 4, 0);
	if(recv(incomingSocket, buffer, 1, 0) <= 0 || buffer[0] != '1')
		return 5;
	
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
	char buffer[2 * 4];
	
	int pin;
	int value;
	
	while((receivedBytes = recv(incomingSocket, buffer, 3, 0)) > 0) {
		memcpy((void*) &pin, (void*) buffer, 4);
		memcpy((void*) &value, (void*) (buffer + 4), 4);
		
		setPinValue(pin, value);
		
		if(send(incomingSocket, "1", 1, 0) != 1)
			printf("Send error\n");
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