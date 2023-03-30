#ifndef NETWORKAPI_H
#define NETWORKAPI_H

#include <iostream>

class IClientConnection
{
public:
    virtual void Connect(const char* ip_addr, int port)=0;
    virtual void Send(const void* buffer, unsigned int size)=0;
};

class IServerConnection
{
public:
    virtual int Receive(char* buffer, int buf_len) = 0;
};

#endif