#ifdef __linux__
#include "LinuxNetworkApi.h"
#else
#include "WinNetworkApi.h"
#endif
#include <fstream>

const char* IP = "127.0.0.1"; 
int PORT = 42032;

int main()
{
    Server server(IP,PORT); //creating server's object and configuring in constructor
    const char* file_path = "logFile.txt";
    std::ofstream log_file;
    const int bufSize = 15; //max length of message
    char buffer[bufSize];
    while(1)
    {
        log_file.open(file_path, std::ios::binary | std::ios::app);
        int read_size = server.Receive(buffer,bufSize);
        printf("%d\n", read_size);
        log_file.write(buffer, read_size);
        log_file.close();
    }
}
