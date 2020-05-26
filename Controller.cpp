#include <iostream>
#include "Server.h"

int main()
{
	std::cout << "----------------------------------------" << std::endl;
	std::cout << "------------Server is running-----------" << std::endl;
	std::cout << "----------------------------------------" << std::endl;
	
	char * data = NULL;
	Server serv;
	SOCKET ClientSocket = INVALID_SOCKET;


	serv.acceptClient(ClientSocket);
	data = serv.reciveData(ClientSocket);
	std::cout << "the data:\n" << data << std::endl;
	serv.closeClient(ClientSocket);

}