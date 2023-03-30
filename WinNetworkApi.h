#include "NetworkApi.h"
#include <iostream>
#include <ws2tcpip.h>

class ClientConnection: public IClientConnection
{
private:
    WORD ver;
    WSADATA wsa_data;
    SOCKET socket_fd;
    sockaddr_in saddr;
public:
    ClientConnection();
    ~ClientConnection();
    void Connect(const char* ip_addr, int port) override;
    void Send(const void* buffer, unsigned int size) override;
};

class Server : public IServerConnection
{
private:
    WSADATA wsa_data;
    //sockets
    SOCKET server_fd;
    SOCKET client_fd;
    //address info
    sockaddr_in saddr_in;
    int saddr_in_len;
    sockaddr_in saddr_from;
    int saddr_from_len;
public:
    Server(const char* ip_addr, int port);
    ~Server();
    int Receive(char* buffer, int buf_len) override;
};

