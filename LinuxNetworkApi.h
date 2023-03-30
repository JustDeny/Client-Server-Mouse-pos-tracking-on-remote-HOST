#ifndef LINUXAPI_H
#define LINUXAPI_H

#include "NetworkApi.h"
#include <pthread.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>



class ClientConnection: public IClientConnection
{
private:
    int socket_fd;
    sockaddr_in saddr;
public:
    ClientConnection();
    ~ClientConnection();
    void Connect(const char* ip_addr, int port) override;
    void Send(const void* buffer, unsigned int size) override;
};

class Server: public IServerConnection
{
private:
    //socket
    int socket_fd;
    int server_fd;
    sockaddr_in saddr;
    socklen_t saddr_len;
public:
    Server(const char* ip_addr, int port);
    ~Server();
    int Receive(char* buffer, int buf_len) override;
};
#endif
