//
// Created by deny on 8/25/22.
//

#ifndef LINUXCLIENTAPI_H
#define LINUXCLIENTAPI_H

#include "ClientApi.h"
#include <linux/input.h>
#include <X11/Xlib.h>
#include <unistd.h>
#include <fcntl.h>

#define MOUSE_FILE "/dev/input/event9"

class Client: public IClient
{
private:
    //for calling XQueryPointer()
    Display* dpy;  int win_x, win_y;
    Window root, child;
    unsigned int mask;

    //for device file
    int device_fd;
    struct input_event ie;

    std::thread t1;
    std::thread t2;
    void GetMouseCoord(MouseInfo& mi);
public:
    Client();
    ~Client();
    void ReadMousePos(MouseInfo& mi) override;
    void ReadMouseClicks(MouseInfo& mi) override;
};

#endif
