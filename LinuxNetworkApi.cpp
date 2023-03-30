#include "LinuxNetworkApi.h"

ClientConnection::ClientConnection() {
    //opening socket
    if ((socket_fd = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP))==-1)
    {
        std::cerr << "Client opening socket failed" << std::endl;
        exit(EXIT_FAILURE);
    }
    memset(&saddr, 0, sizeof saddr);
}

void ClientConnection::Connect(const char* ip_addr, int port)
{
    //filling host address info
    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(port);
    inet_pton(AF_INET,ip_addr, &saddr.sin_addr);

    if((connect(socket_fd,(sockaddr*)&saddr, sizeof saddr)) == -1)
    {
        std::cerr<< "Client connection failed" << std::endl;
        close(socket_fd);
        exit(EXIT_FAILURE);
    }
}

void ClientConnection::Send(const void* buffer, unsigned int size)
{
    if(send(socket_fd,buffer,size,0)== -1)
    {
        std::cerr<<"Client transmission failed" << std::endl;
        close(socket_fd);
        exit(EXIT_FAILURE);
    }
}

ClientConnection::~ClientConnection() {
    close(socket_fd);
}

int Server::Receive(char *buffer, int buf_len) {
    unsigned int ret_size = recv(server_fd, buffer, buf_len, 0);
    std::cout<<buffer << std::endl;
    return ret_size;
}

Server::Server(const char* ip_addr, int port) {
    //opening socket
    saddr_len = sizeof saddr;
    socket_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(socket_fd < 0)
    {
        std::cerr <<"Server socket creation" << std::endl;
        exit(EXIT_FAILURE);
    }
    //filling server address info to bind
    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(port);
    inet_pton(AF_INET,ip_addr,&saddr.sin_addr);

    if(bind(socket_fd, (sockaddr*)&saddr, sizeof saddr) < 0)
    {
        std::cerr <<"Failed to bind" << std::endl;
        close(socket_fd);
        exit(EXIT_FAILURE);
    }
    if(listen(socket_fd, 3)<0)
    {
        std::cerr <<"Failed to listen" << std::endl;
        close(socket_fd);
        exit(EXIT_FAILURE);
    }
    if((server_fd = accept(socket_fd, (sockaddr*)&saddr, &saddr_len)) < 0)
    {
        std::cerr <<"Failed to accept" << std::endl;
        close(socket_fd);
        exit(EXIT_FAILURE);
    }
}

Server::~Server() {
    close(server_fd);
    close(socket_fd);
}
