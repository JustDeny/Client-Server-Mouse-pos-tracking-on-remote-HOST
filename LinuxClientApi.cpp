#include "LinuxClientApi.h"

//definition of variables with external linkage
std::mutex mtx;
MouseInfo mouse_info;
std::atomic<bool> ready_to_send(false);

Client::Client():
        dpy(XOpenDisplay(NULL)), t1(&Client::ReadMousePos,this,std::ref(mouse_info)),
        t2(&Client::ReadMouseClicks, this, std::ref(mouse_info))

{
    //opening device file to get mouse events
    if ((device_fd = open(MOUSE_FILE, O_RDONLY))== -1)
    {
        std::cerr << ("opening device") << std::endl;
        exit(EXIT_FAILURE);
    }
}

void Client::ReadMousePos(MouseInfo &mi)
{
    while(1)
    {
        usleep(500*1000);   // read mouse coord each 500ms
        {
            std::lock_guard<std::mutex> lock(mtx);
            GetMouseCoord(mi);
            mi.code = NONE;
            ready_to_send.store(true);
        }
    }
}


void Client::GetMouseCoord(MouseInfo &mi) {
    XQueryPointer(dpy, XDefaultRootWindow(dpy), &root,&child,&mi.xCoord, &mi.yCoord,&win_x,&win_y, &mask);
}

void Client::ReadMouseClicks(MouseInfo &mi) {
    // reading from device file for moose buttons
    while (read(device_fd, (void*)&ie, sizeof(struct input_event)))
    {
        //if mouse button click event
        if(ie.type == 1)
        {
            //if pressed down
            if(ie.value == 1)
            {
                std::lock_guard<std::mutex> lock(mtx);
                GetMouseCoord(mi);
                mi.code = ie.code;
                ready_to_send.store(true);
            }
        }
    }
}

Client::~Client() {
    t1.join();
    t2.join();
}
