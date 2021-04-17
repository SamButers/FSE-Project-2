#ifndef SOCKET_H_
#define SOCKET_H_

#include <sys/socket.h>
#include <sys/un.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>

#include <stdio.h>

#define SERVER_IP "192.168.0.53"
#define SERVER_PORT 10030
#define PORT 10130

extern int clientSocket;
extern int serverSocket;
extern pthread_t serverThread;

int initClient();
int initServer();
void joinClient();
void joinServer();
void sendPinUpdate(int pin, int value);
void* connectionHandler(void *args);

#endif