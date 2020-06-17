#include <iostream>
#include <fstream>
#include <string.h>
#include "DataBase.h"

using namespace std;

//------------------------------------
DataBase::DataBase(string name)
{
	fileName = name;
}
//-----------------------------------------
//update the csv file by the new matrix
//------------------------------------------
int DataBase::updateMatrix(Matrix& mat)
{
	fstream f;
	f.open(fileName);
	for (int i = 0; i < mat.rows; i++) {
		for (int j = 0; j < mat.columns; j++) {

			f << mat.getDataByIndex(i,j)<<",";

		}
		f << "\n";  
	}
	f.close();
	return 1;
}
//----------------------------------------
string DataBase::getFile()
{
	return fileName;
}
DataBase::~DataBase() {
}