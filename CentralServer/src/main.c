#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <arpa/inet.h>
#include <unistd.h>

#define SERVER_IP "192.168.0.52"
#define SERVER_PORT 10030

int serverSocket;
int clientSocket;

void TCPHandle(int socket) {
	char buffer[16];
	int length;
	
	if((length = recv(socket, buffer, 16, 9)) < 0)
		printf("Socket receive error.\n");
	
	while(length > 0) {
		printf("Received: %s\n" buffer);
		
		if((length = recv(socket, buffer, 16, 9)) < 0)
			printf("Socket receive error.\n");
	}	
}

int main() {
	int attempts = 0;
	struct sockaddr_in serverAddr;
	struct sockaddr_in clientAddr;
	unsigned int clientLength;
	
	if((serverSocket = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		printf("Socket initialization error.\n");
		return 0;
	}
	
	memset(&serverAddr, 0, sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	serverAddr.sin_port = htons(SERVER_PORT);
	
	if(bind(serverSocket, (struct sockaddr *) &serverAddr, sizeof(serverAddr)) < 0) {
		printf("Socket binding error.\n");
		return 0;
	}
	
	if(listen(serverSocket, 1) < 0) {
		printf("Socket listen error.\n");
		return 0;
	}

	while(1) {
		clientLength = sizeof(clientAddr);
		if((clientSocket = accept(serverSocket, (struct sockaddr*) &clientAddr, &clientLength)) < 0) {
			printf("Socket accept error.\n");
			continue;
		}
		
		printf("Conexão do cliente: %s\n", inet_ntoa(clientAddr.sin_addr));
		
		if(connect(clientSocket, (struct sockaddr*) &serverAddr, sizeof(serverAddr)))
			break;
			
		sleep(1);
	}
	
	close(serverSocket);
	
	return 0;
}