#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <arpa/inet.h>
#include <unistd.h>

#define SERVER_IP "192.168.0.52"
#define SERVER_PORT 10030

int clientSocket;

int main() {
	int attempts = 0;
	struct sockaddr_in serverAddr;
	
	if((clientSocket = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		printf("Socket initialization error.\n");
		return 0;
	}
	
	memset(&serverAddr, 0, sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.s_addr = inet_addr(SERVER_IP);
	serverAddr.sin_port = htons(SERVER_PORT);

	while(1) {
		if(attempts > 5) {
			printf("Socket connection error.\n");
			return 0;
		}
		
		if(connect(clientSocket, (struct sockaddr*) &serverAddr, sizeof(serverAddr)))
			break;
			
		sleep(1);
	}
	
	close(clientSocket);
	
	return 0;
}