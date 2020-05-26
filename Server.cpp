#undef UNICODE

#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include "Server.h"

// Need to link with Ws2_32.lib
#pragma comment (lib, "Ws2_32.lib")
// #pragma comment (lib, "Mswsock.lib")

#define DEFAULT_BUFLEN 1024
#define DEFAULT_PORT "27015"
//----------------------------------------------------------------
//ctr of the class
Server::Server()
{
	ListenSocket = INVALID_SOCKET;
	result = NULL;
	WSADATA wsaData;
	init(wsaData);
	initServer();
	connectToSocket();
	bindSocket();
	freeaddrinfo(result);
	listenSocket();
}
//---------------------------------------------------------
//init the Winsock - for socket on windows
void Server::init(WSADATA & wsaData)
{
	// Initialize Winsock
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) {
		std::cout << "WSAStartup failed with error: " << iResult << std::endl;
		exit(1);
	}
}
//---------------------------------------------------------------
//init the sever socket
void Server::initServer()
{
	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	hints.ai_flags = AI_PASSIVE;

	// Resolve the server address and port
	iResult = getaddrinfo(NULL, DEFAULT_PORT, &hints, &result);
	if (iResult != 0) {
		std::cout << "getaddrinfo failed with error: " << iResult << std::endl;
		WSACleanup();
		exit(1);
	}
}
//-----------------------------------------------------------------
//connect to server socket
void Server::connectToSocket()
{
	// Create a SOCKET for connecting to server
	ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
	if (ListenSocket == INVALID_SOCKET) {
		std::cout << "socket failed with error: " << WSAGetLastError() << std::endl;
		freeaddrinfo(result);
		WSACleanup();
		exit(1);
	}
}
//-------------------------------------------------------------------
void Server::bindSocket()
{
	// Setup the TCP listening socket
	iResult = bind(ListenSocket, result->ai_addr, (int)result->ai_addrlen);
	if (iResult == SOCKET_ERROR) {
		std::cout << "bind failed with error: " << WSAGetLastError() << std::endl;
		freeaddrinfo(result);
		closesocket(ListenSocket);
		WSACleanup();
		exit(1);
	}
}
//---------------------------------------------------------------------
//listen to socket
void Server::listenSocket()
{
	iResult = listen(ListenSocket, SOMAXCONN);
	if (iResult == SOCKET_ERROR) {
		std::cout << "listen failed with error: " << WSAGetLastError() << std::endl;
		closesocket(ListenSocket);
		WSACleanup();
		exit(1);
	}
}
//------------------------------------------------------------
//accept new client
int Server::acceptClient(SOCKET& ClientSocket)
{
	// Accept a client socket
	ClientSocket = accept(ListenSocket, NULL, NULL);
	if (ClientSocket == INVALID_SOCKET) {
		return 1;
	}
	std::cout << "Client fd number " << ClientSocket << " is done" << std::endl;
	return 0;
}
//-------------------------------------------------------------
//recive the data from client
char * Server::reciveData(SOCKET& ClientSocket)
{
	char *recvbuf = (char*)malloc(10*sizeof(char));
	if (recvbuf == NULL)
		exit(1);
	char *recvdata = (char*)malloc(DEFAULT_BUFLEN);
	if (recvdata == NULL)
		exit(1);

	memset(recvdata, 0, sizeof(recvdata));
	// Receive until the peer shuts down the connection
	do {
		memset(recvbuf, 0, sizeof(recvbuf));

		iResult = recv(ClientSocket, recvbuf, 10, 0);

		if (iResult > 0) {
			recvbuf[10] = '\0'; //delete the gibrish chars
			strcat(recvdata, recvbuf); 
		}
		else if (iResult == 0)
		{
			std::cout << "-----------------------------------------------" << std::endl;
			std::cout << "------------Client connection closing----------" << std::endl;
			std::cout << "-----------------------------------------------" << std::endl;
			//free(recvbuf);
			return recvdata;
		}
		else {
			std::cout << "recv failed with error: " << WSAGetLastError() << std::endl;
			closesocket(ClientSocket);
			WSACleanup();
			//free(recvbuf);
			exit(1);
		}

	} while (iResult > 0);
	
	//free(recvbuf);
	return recvdata;
}
//----------------------------------------------------------------
//close client socket
void Server::closeClient(SOCKET & ClientSocket)
{
	// cleanup
	closesocket(ClientSocket);
	WSACleanup();
}
//----------------------------------------------------------------
Server::~Server()
{
	std::cout << "---------------------------------------------" << std::endl;
	std::cout << "------------Server socket closeing-----------" << std::endl;
	std::cout << "---------------------------------------------" << std::endl;
}
//-----------------------------------------------------------------
