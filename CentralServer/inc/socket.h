#ifndef SOCKET_H_
#define SOCKET_H_

#include <sys/socket.h>
#include <sys/un.h>
#include <arpa/inet.h>

#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>

#include "pin.h"

#define SERVER_IP "192.168.0.4"
#define SERVER_PORT 10130
#define PORT 10030

typedef struct BMEData {
	float temperature, humidity;
} BMEData;

extern int clientSocket;
extern int serverSocket;
extern pthread_t serverThread;

int initClient();
int initServer();
void joinClient();
void joinServer();
int sendPinUpdate(int pin);
void getBMEData(BMEData *data);
void* connectionHandler(void *args);

#endif