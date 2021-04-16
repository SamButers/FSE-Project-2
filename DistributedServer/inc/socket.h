#ifndef SOCKET_H_
#define SOCKET_H_

#include <sys/socket.h>
#include <sys/un.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

#define SERVER_IP "192.168.0.52"
#define SERVER_PORT 10030

void initClient(int *socket);
int initServer();

#endif