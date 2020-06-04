#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <windows.h>
#include <time.h>  
using namespace std;


// Need to link with Ws2_32.lib, Mswsock.lib, and Advapi32.lib
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")


#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "27015"
SOCKET start(string sendbuf);
void fillData(struct Frame *frame);

struct Frame
{
	short data[20];
	bool flag;
};

int main()
{
	SOCKET ConnectSocket = start();
	srand(time(NULL));
	struct Frame *frame;

	for (int i = 0; i < 10; i++) {
		
		Sleep(30000);
		
		fillData(frame);
		frame->flag = (i % 2 == 0) ? true : false;

		// Send an initial buffer
		int iResult = send(ConnectSocket, (const char*)frame, (int)sizeof(frame), 0);
		if (iResult == SOCKET_ERROR) {
			cout << "send failed with error: " << WSAGetLastError() << "\n";
			closesocket(ConnectSocket);
			WSACleanup();
			exit(1);

		}
		cout << "Bytes Sent: " << iResult << "\n";
	
	}

	return 0;
}
SOCKET start(){
	WSADATA wsaData;
	SOCKET ConnectSocket = INVALID_SOCKET;
	struct addrinfo* result = NULL,
		* ptr = NULL,
		hints;
	char recvbuf[DEFAULT_BUFLEN];
	int iResult;
	int recvbuflen = DEFAULT_BUFLEN;

	

	// Initialize Winsock
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) {
		cout<<"WSAStartup failed with error:"<< iResult<<"\n";
		exit(1);

	}

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	// Resolve the server address and port
	iResult = getaddrinfo("loclhost", DEFAULT_PORT, &hints, &result);
	if (iResult != 0) {
		cout<<"getaddrinfo failed with error:"<< iResult "\n";
		WSACleanup();
		exit(1);

	}

	// Attempt to connect to an address until one succeeds
	for (ptr = result; ptr != NULL; ptr = ptr->ai_next) {

		// Create a SOCKET for connecting to server
		ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype,
			ptr->ai_protocol);
		if (ConnectSocket == INVALID_SOCKET) {
			printf("socket failed with error: %ld\n", WSAGetLastError());
			WSACleanup();
			exit(1);

		}

		// Connect to server.
		iResult = connect(ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
		if (iResult == SOCKET_ERROR) {
			closesocket(ConnectSocket);
			ConnectSocket = INVALID_SOCKET;
			continue;
		}
		break;
	}

	freeaddrinfo(result);

	if (ConnectSocket == INVALID_SOCKET) {
		cout<<"Unable to connect to server!\n";
		WSACleanup();
		exit(1);

	}

	// shutdown the connection since no more data will be sent
	iResult = shutdown(ConnectSocket, SD_SEND);
	if (iResult == SOCKET_ERROR) {
		cout<<"shutdown failed with error: "<< WSAGetLastError()<<"\n", );
		closesocket(ConnectSocket);
		WSACleanup();
		exit(1);
	}

	// cleanup
	closesocket(ConnectSocket);
	WSACleanup();
}
void fillData(struct Frame *frame)
{
	int r = (rand() % 100) + 1;
	for (int i = 0; i < 20; i++)
	{
		frame->data[i] = r;
		r = (rand() % 100) + 1;
	}
}