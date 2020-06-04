#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <windows.h>
#include <time.h> 
#include <vector>
#include<string>

#define NUM_OF_VALUES 20
#define FLOAT_LENGTH_TO_CHAR 20
#define DEFAULT_PORT "27015"
#define DEFAULT_BUFLEN 512
using namespace std;


// Need to link with Ws2_32.lib, Mswsock.lib, and Advapi32.lib
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")


void start(SOCKET &ConnectSocket);
void fillData(vector<float> &data);
void fillData(vector<float> &data, int type);
char* fromVectorToChar(vector<float> &v);
void print(std::vector <float> const &a);
void ftoa(float n, char* res, int afterpoint);
int intToStr(int x, char str[], int d);
void reverse(char* str, int len);



int main()
{
	SOCKET ConnectSocket = INVALID_SOCKET;
	srand((unsigned int)time(NULL));
	vector<float> data(NUM_OF_VALUES + 1, 0);

	for (int i = 0; i < 10; i++) {
		
		start(ConnectSocket);
		Sleep(5000);
		if(i%2==0)
			fillData(data);
		else fillData(data, 0);
		print(data);
		char* tmpData = fromVectorToChar(data);
		cout << tmpData << endl;

		// Send an initial buffer
		int iResult = send(ConnectSocket, (char*)tmpData, (int)strlen((char*)tmpData), 0);
		if (iResult == SOCKET_ERROR) {
			cout << "send failed with error: " << WSAGetLastError() << "\n";
			closesocket(ConnectSocket);
			WSACleanup();
			exit(1);

		}
		cout << "Bytes Sent: " << iResult << "\n";
		//close connction
		//---------------------------------------------------------
		// shutdown the connection since no more data will be sent
		iResult = shutdown(ConnectSocket, SD_SEND);
		if (iResult == SOCKET_ERROR) {
			cout << "shutdown failed with error: " << WSAGetLastError() << "\n";
			closesocket(ConnectSocket);
			WSACleanup();
			exit(1);
		}

		// cleanup
		closesocket(ConnectSocket);
		WSACleanup();
	}

	return 0;
}
//-------------------------------------------------------------
//connect to socket
void start(SOCKET &ConnectSocket){
	WSADATA wsaData;
	struct addrinfo* result = NULL,
		* ptr = NULL,
		hints;
	int iResult;


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
	iResult = getaddrinfo("localhost", DEFAULT_PORT, &hints, &result);
	if (iResult != 0) {
		cout<<"getaddrinfo failed with error:"<< iResult <<"\n";
		WSACleanup();
		exit(1);

	}

	// Attempt to connect to an address until one succeeds
	for (ptr = result; ptr != NULL; ptr = ptr->ai_next) {

		// Create a SOCKET for connecting to server
		ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
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
}
//----------------------------------------
//the function fill the vector with random values
void fillData(vector<float> &data)
{
	int i;
	float r = 100.0 * ((((float)rand()) / (float)RAND_MAX)) + 40.0;
	for (i = 0; i < NUM_OF_VALUES; i++)
	{
		data[i] = r;
		r = 100.0 * ((((float)rand()) / (float)RAND_MAX)) + 40.0;
	}
	data[i] = (float)1;
}
//-----------------------------------------
//the function fill the vector with random values
void fillData(vector<float> &data, int type)
{
	int indexI, indexJ, i;
	indexI = (rand() % 100);
	indexJ = (rand() % 100);
	float r;
	for (i = 0; i < NUM_OF_VALUES; ++i)
	{
		r = 100.0 * ((((float)rand()) / (float)RAND_MAX)) + 40.0;
		short temp = (short)(indexI << 8 | indexJ);
		data[i] = (i % 2 == 0) ? (float)temp : r;
	}
	data[i] = (float)0;
}
//---------------------------------------
//convert the vector to char array
char* fromVectorToChar(vector<float> &v)
{
	int i, j;
	char* buff = new char[v.size() * FLOAT_LENGTH_TO_CHAR];
	memset(buff, 0, sizeof(buff));
	char res[20];
	for (i = 0; i < v.size(); i++)
	{
		ftoa(v[i], res, 4);
		strcat(buff, res);
		memset(res, 0, sizeof(res));
	}
	return buff;
}
//-------------------------------------------------------------------------
// print vector
void print(std::vector <float> const &a)
{
	std::cout << "The vector elements are : \n";

	for (int i = 0; i < a.size(); i++)
		std::cout << a.at(i) << ' ';
	std::cout << endl;
}
//--------------------------------------------------------------------------
//this part of converting float to char buffer
//--------------------------------------------------------------------------

// Reverses a string 'str' of length 'len' 
void reverse(char* str, int len)
{
	int i = 0, j = len - 1, temp;
	while (i < j) {
		temp = str[i];
		str[i] = str[j];
		str[j] = temp;
		i++;
		j--;
	}
}

// Converts a given integer x to string str[].  
// d is the number of digits required in the output.  
// If d is more than the number of digits in x,  
// then 0s are added at the beginning. 
int intToStr(int x, char str[], int d)
{
	int i = 0;
	while (x) {
		str[i++] = (x % 10) + '0';
		x = x / 10;
	}

	// If number of digits required is more, then 
	// add 0s at the beginning 
	while (i < d)
		str[i++] = '0';

	reverse(str, i);
	str[i] = '\0';
	return i;
}

// Converts a floating-point/double number to a string. 
void ftoa(float n, char* res, int afterpoint)
{
	// Extract integer part 
	int ipart = (int)n;

	// Extract floating part 
	float fpart = n - (float)ipart;

	// convert integer part to string 
	int i = intToStr(ipart, res, 0);

	// check for display option after point 
	if (afterpoint != 0) {
		res[i] = '.'; // add dot 

					  // Get the value of fraction part upto given no. 
					  // of points after dot. The third parameter  
					  // is needed to handle cases like 233.007 
		fpart = fpart * pow(10, afterpoint);

		intToStr((int)fpart, res + i + 1, afterpoint);
	}
}
//-------------------------------------------------------------------