#include "socket.h"
#include <stdio.h>

int clientSocket;
int serverSocket;
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
	int incomingSocket;
	
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
		
	pthread_create(&serverThread, NULL, &connectionHandler, (void*) &incomingSocket);
	return 0;
}

void sendPinUpdate(int pin, int value) {
	printf("Pin Update %d: %d\n", pin, value);
	return;
}

void* connectionHandler(void *args) {
	printf("Handler initialized\n");
	int *incomingSocket = (int*) args;
	
	int receivedBytes;
	char buffer[32];
	
	while((receivedBytes = recv(*incomingSocket, buffer, 32, 0)) > 0) {
		if(send(*incomingSocket, buffer, receivedBytes, 0) != receivedBytes)
			printf("Send error\n");
			
		printf("%s\n", buffer);
	}
	
	close(*incomingSocket);
	return NULL;
}

void joinClient() {
	close(clientSocket);
}

void joinServer() {
	pthread_cancel(serverThread);
	close(serverSocket);
	//close(incomingSocket);
}