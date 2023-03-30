#ifdef __linux__
#include "LinuxNetworkApi.h"
#include "LinuxClientApi.h"
#else
#include "WinNetworkApi.h"
#include "WinClientApi.h"
#endif

#include <fstream>
#include <sstream>


const char* IP = "127.0.0.1";
int PORT = 42032;

unsigned int CreateMessage(char* mes, MouseInfo& mi) {
    std::stringstream ss;
    ss << mi.xCoord << "x" << mi.yCoord;
    if (mi.code == LMB) {   // left mouse button
        ss << " LCM";
    } else if (mi.code == RMB) {    // right mouse button
        ss << " RCM";
    }
    ss << "\n";
    unsigned int length = ss.str().size();    //length of generated message
    std::memcpy(mes, ss.str().c_str(), length); //copying message in buffer to be read from
    return length;
}

int main()
{
    ClientConnection client_con;
    client_con.Connect(IP, PORT);
    Client client;
    const int msg_size = 15;
    char message[msg_size];
    unsigned int curr_size = 0;
    while(1)
    {
        if(ready_to_send)
        {
            std::lock_guard<std::mutex> lock(mtx);
            curr_size = CreateMessage(message, mouse_info);
            printf("%d\n", curr_size);
            client_con.Send(message, curr_size);
            message[curr_size] = '\0';  //limiting buffer preventing from reading remains of longer messages
            ready_to_send = false;
        }
    }
    return 0;
}
