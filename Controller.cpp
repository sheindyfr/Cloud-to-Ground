#include <iostream>
#include "Server.h"

int main()
{
	std::cout << "----------------------------------------" << std::endl;
	std::cout << "------------Server is running-----------" << std::endl;
	std::cout << "----------------------------------------" << std::endl;
	
	char * data = NULL;
	Server::Server(&data);
	std::cout << "the data:\n" << data << std::endl;
}