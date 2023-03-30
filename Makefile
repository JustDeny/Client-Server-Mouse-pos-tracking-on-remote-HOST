FLAGS = -Wall -Wextra -pedantic
LINKFLAGS = 
CLIENT_FILES = ClientApplication.cpp
SERVER_FILES = ServerApplication.cpp

ifeq ($(OS),Windows_NT) #windows
	CLIENT_FILES += WinClientApi.cpp 
	CLIENT_FILES += WinNetworkApi.cpp
	SERVER_FILES += WinNetworkApi.cpp
	FLAGS += -lws2_32
else # *nix os
	CLIENT_FILES += LinuxClientApi.cpp LinuxNetworkApi.cpp
	SERVER_FILES += LinuxNetworkApi.cpp
	FLAGS += -lX11 -pthread -latomic
endif
all: $(CLIENT_FILES) $(SERVER_FILES)
	@echo "####################Building project####################"
	g++ $(CLIENT_FILES) -o clientApp $(FLAGS)
	g++ $(SERVER_FILES) -o serverApp $(FLAGS)
clean:
	@echo "Cleaning project..."
	rm clientApp serverApp
