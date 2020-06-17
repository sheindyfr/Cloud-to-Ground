#include <iostream>
#include <vector>
#include <string>
#include "Server.h"
#include "Matrix.h"
#include "Frame.h"
#include "DataBase.h"

void fromCharArrToVector(std::vector<float> &v, char* buff);
void printVector(std::vector <float> const &a);

int main()
{
	std::cout << "----------------------------------------" << std::endl;
	std::cout << "------------Server is running-----------" << std::endl;
	std::cout << "----------------------------------------" << std::endl;
	

	Server serv;
	SOCKET ClientSocket = INVALID_SOCKET;
	Matrix mat;
	DataBase DB("out.csv");


	while (1) 
	{
		//---------------------------------------------------------------------
		// Recive the data from the client
		//---------------------------------------------------------------------
		serv.acceptClient(ClientSocket);
		
		char * tmpData = NULL;
		tmpData = serv.reciveData(ClientSocket);
		
		std::vector<float> data;
		// convert the char* to a float vector
		fromCharArrToVector(data, tmpData);

		//---------------------------------------------------------------------
		// Start load the data
		//---------------------------------------------------------------------

		Frame frame(data);
		if (frame.getType() == fullFrame)
		{
			frame.createMatrix(mat);
		}
		else frame.figureAndCreateMatrix(mat);
		mat.printMatrix();

		DB.updateMatrix(mat);

	}
	//serv.closeClient(ClientSocket);
	//---------------------------------------------------------------------
	return 0;
}

//-------------------------------------------------------------------------
// convert the data that recived, from char array to a float vector
//-------------------------------------------------------------------------
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
//---------------
// print vector
//---------------
void printVector(std::vector <float> const &a) 
{
	std::cout << "The vector elements are : \n";

	for (int i = 0; i < a.size(); i++)
		std::cout << a.at(i) << ' ';
	std::cout << std::endl;
}
//--------------------------------------------------------------------------
