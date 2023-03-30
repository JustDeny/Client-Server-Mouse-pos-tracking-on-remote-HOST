#include "WinNetworkApi.h"

ClientConnection::ClientConnection()
{
	//initializing socket version etc.
	ver = MAKEWORD(2, 2);
	if (WSAStartup(ver, &wsa_data) != 0)
	{
		std::cerr << "Client WSAStartup failed" << std::endl;
		exit(EXIT_FAILURE);
	}
	if ((socket_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET)
	{
		std::cerr << "Invalid client socket" << std::endl;
		exit(EXIT_FAILURE);
	}
}
ClientConnection::~ClientConnection() 
{
	closesocket(socket_fd);
};
void ClientConnection::Connect(const char* ip_addr, int port)
{
	//filling host address info
	saddr.sin_family = AF_INET;
	saddr.sin_port = htons(port);
	inet_pton(AF_INET, ip_addr, &saddr.sin_addr);
	int connect_res = connect(socket_fd, (sockaddr*)&saddr, sizeof saddr);
	if (connect_res == SOCKET_ERROR)
	{
		std::cerr << "Client connection failed" << std::endl;
		exit(EXIT_FAILURE);
	}
	printf("Client connected to server\n");
}
void ClientConnection::Send(const void* buffer, unsigned int size)
{
	if (send(socket_fd, (const char*)buffer, size, 0) == SOCKET_ERROR)
	{
		this->~ClientConnection();
		std::cerr << "Cient transmission failed" << std::endl;
		exit(EXIT_FAILURE);
	}
}

Server::Server(const char* ip_addr, int port)
{
	//initializing client socket version etc.
	WORD ver = MAKEWORD(2, 2);
	if (WSAStartup(ver, &wsa_data) != 0)
	{
		std::cerr << "Server WSAStartup failed" << std::endl;
		exit(EXIT_FAILURE);
	}
	server_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (server_fd == INVALID_SOCKET)
	{
		std::cerr << "Invalid server socket" << std::endl;
		exit(EXIT_FAILURE);
	}
	saddr_in.sin_family = AF_INET;
	saddr_in.sin_port = htons(port);
	saddr_in.sin_addr.S_un.S_addr = INADDR_ANY;
	saddr_in_len = sizeof saddr_in;
	if (bind(server_fd, (sockaddr*)&saddr_in, saddr_in_len) != 0)
	{
		std::cerr << "Failed to bind server socket" << std::endl;
		exit(EXIT_FAILURE);
	}
	if (listen(server_fd, 3) != 0)
	{
		std::cerr << "Failed to listen" << std::endl;
		exit(EXIT_FAILURE);
	}
	saddr_from_len = sizeof saddr_from;
	if((client_fd = accept(server_fd,(sockaddr*)&saddr_from, &saddr_from_len))==INVALID_SOCKET)
	{ 
		std::cerr << "Failed to accept" << std::endl;
		exit(EXIT_FAILURE);
	}
	std::cout << "Server accepted client connection" << std::endl;
}

Server::~Server()
{
	closesocket(client_fd);
	closesocket(server_fd);
	WSACleanup();
}

int Server::Receive(char* buffer, int buf_len)
{
	int recv_size = recv(client_fd, buffer, buf_len, 0);
	if (recv_size < 0)
	{
		std::cerr << "Server recieve error (negative number of bytes)" << std::endl;
	}
	return 	recv_size;
}