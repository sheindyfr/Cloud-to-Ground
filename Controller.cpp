#include <iostream>
#include <vector>
#include <string>
#include "Server.h"
#define N 4
#define M 5

void fromCharArrToVector(std::vector<float> &v, char* buff);
void print(std::vector <float> const &a);

int main()
{
	//---------------------------------------------------------------------
	// Recive the data from the client
	//---------------------------------------------------------------------
	std::cout << "----------------------------------------" << std::endl;
	std::cout << "------------Server is running-----------" << std::endl;
	std::cout << "----------------------------------------" << std::endl;
	

	char * tmpData = NULL;
	std::vector<float> data;
	Server serv;
	SOCKET ClientSocket = INVALID_SOCKET;

	while (1) 
	{
		serv.acceptClient(ClientSocket);
		tmpData = serv.reciveData(ClientSocket);
		std::cout << tmpData << std::endl;
		fromCharArrToVector(data, tmpData);
		print(data);
	}
	//serv.closeClient(ClientSocket);
	//---------------------------------------------------------------------

}

//-------------------------------------------------------------------------
// convert the data to a float vector
void fromCharArrToVector(std::vector<float> &v, char* buff)
{
	int i, j = 0;
	for (i = 0; i < strlen((char*)buff); i++)
	{
		std::string tmp = "";
		float val;
		while (buff[i] != '.')
		{
			tmp += buff[i];
			i++;
		}
		val = (float)std::stoi(tmp);
		std::string tmp2 = "";
		i++;
		for (int k = 0; k < 4; k++)
		{
			tmp2 += buff[i];
			i++;
		}
		if (buff[i] == '.')
		{
			v.push_back(0.0);
			break;
		}
		float b = float(std::stoi(tmp2) / 10000.0);
		val += b;
		v.push_back(val);
		i--;
	}
}
//-------------------------------------------------------------------------
// print vector
void print(std::vector <float> const &a) 
{
	std::cout << "The vector elements are : \n";

	for (int i = 0; i < a.size(); i++)
		std::cout << a.at(i) << ' ';
	std::cout << std::endl;
}
//--------------------------------------------------------------------------
