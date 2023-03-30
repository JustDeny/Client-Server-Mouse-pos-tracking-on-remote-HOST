#ifndef WINCLIENTAPI_H
#define WINCLIENTAPI_H

#include "ClientApi.h"
#include <windows.h>
#include <chrono>

class Client: public IClient
{
private:
    std::thread t1; //thread checking mouse pos each 500ms
    std::thread t2; //thread detecting mouse clicks and its coords
    void GetMouseCoord(MouseInfo& mi);
public:
    Client();
    ~Client();
    void ReadMousePos(MouseInfo& mi) override;
    void ReadMouseClicks(MouseInfo& mi) override;
};
#endif
