#include <iostream>
#include <vector>
#include <string>
#include "Server.h"

void fromCharArrToVector(std::vector<float> &v, char* buff);
void print(std::vector <float> const &a);

int main()
{
	std::cout << "----------------------------------------" << std::endl;
	std::cout << "------------Server is running-----------" << std::endl;
	std::cout << "----------------------------------------" << std::endl;
	

	Server serv;
	SOCKET ClientSocket = INVALID_SOCKET;

	while (1) 
	{
		//---------------------------------------------------------------------
		// Recive the data from the client
		//---------------------------------------------------------------------
		serv.acceptClient(ClientSocket);
		
		char * tmpData = NULL;
		tmpData = serv.reciveData(ClientSocket);
		std::cout << tmpData << std::endl;
		
		std::vector<float> data;
		fromCharArrToVector(data, tmpData);
		print(data);
		//---------------------------------------------------------------------
		// Start progress the data
		//---------------------------------------------------------------------



		/* TODO: 
		   1. figure out the type of frame.
		   2. create frame object with the data vector (without the last place) and type.
		   3. Matrix mat = halfFrame.figureAndCreateMatrix() --> read the last matrix from the file and return the new with the updates.
		   4. Matrix mat = fullFrame.createMatrix() --> create new matrix by the full frame.
		   5. DB.updateMatrix(mat) --> delete the old mat from the file and write the new.
		*/


	}
	//serv.closeClient(ClientSocket);
	//---------------------------------------------------------------------
	return 0;
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
		while (buff[i] != '.')  // take the integer type of the number
		{
			tmp += buff[i];
			i++;
		}
		val = (float)std::stoi(tmp);
		std::string tmp2 = "";
		i++;
		for (int k = 0; k < 4; k++) // take 4 digits after the point
		{
			tmp2 += buff[i];
			i++;
		}
		if (buff[i] == '.')  // situation of '0' in the end of the vector
		{
			v.push_back(0.0);
			break;
		}
		float b = float(std::stoi(tmp2) / 10000.0);  // convert the 4 digits to a float number between 0 to 1
		val += b;
		v.push_back(val); // add the number to the vector
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
