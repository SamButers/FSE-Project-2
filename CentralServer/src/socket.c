#include "socket.h"

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
		
	int PIN_BYTES = INPUT_PINS_NUM * 4;
	unsigned char *buffer = malloc(PIN_BYTES);
		
	if(recv(clientSocket, buffer, PIN_BYTES, 0) == PIN_BYTES) {
		for(int c = 0; c < INPUT_PINS_NUM; c++)
			memcpy((void*) (INPUT_PINS + c), (void*) (buffer + (4 * c)), 4);
	}
	
	else
		return 3;
	
	free(buffer);
		
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

void* connectionHandler(void *args) {
	printf("Handler initialized\n");
	
	int receivedBytes;
	char buffer[8];
	
	int pin;
	int value;
	
	while((receivedBytes = recv(incomingSocket, buffer, 8, 0)) > 0) {
		memcpy((void*) &pin, (void*) buffer, 4);
		memcpy((void*) &value, (void*) (buffer + 4), 4);
		
		updatePin(pin, value);
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