#ifndef CLIENTAPI_H
#define CLIENTAPI_H

//common headers for linux and windows
#include <thread>
#include <mutex>
#include <atomic>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <iostream>

struct MouseInfo
{
    int xCoord;
    int yCoord;
    unsigned short code;    //code for detecting LMB(272) and RMB(273) and nothing if 0
};

enum MBUTTON
{
    NONE = 0,
    LMB = 272,
    RMB = 273
};

//common for each OS
extern std::mutex mtx;
extern MouseInfo mouse_info;                // shared object used by several threads
extern std::atomic<bool> ready_to_send;     //flag to let thread waiting changes to send info

class IClient
{
public:
    virtual void ReadMousePos(MouseInfo& mi) = 0;
    virtual void ReadMouseClicks(MouseInfo& mi) = 0;
};

#endif
