
#include "Matrix.h"

//---------------------
// default constructor
//---------------------
Matrix::Matrix()
{
	rows = N;
	columns = M;
}

//-------------------------------------------
// the function set the Matrix by new vector
//-------------------------------------------
void Matrix::setData(std::vector<float>& vData)
{
	int i, j, k = 0;
	for (i = 0; i < rows; ++i)
	{
		for (j = 0; j < columns; ++j)
		{
			data[i][j] = vData[k];
			k++;
		}
	}
}

//-----------------------------------------------------
// the function update specific location of the matrix
//-----------------------------------------------------
void Matrix::updateValueByIndex(int i, int j, float val)
{
	data[i][j] = val;
}

//-------------------------------
// the function print the Matrix
//-------------------------------
void Matrix::printMatrix()
{
	int i, j;
	for (i = 0; i < rows; ++i)
	{
		for (j = 0; j < columns; ++j)
		{
			std::cout << data[i][j] << "	";
		}
		std::cout << std::endl;
	}
}
//--------------------------------
// the function return the data by the indexes
//----------------------------
float Matrix::getDataByIndex(int i, int j)
{
	return data[i][j];
}

//-----------------------------------------
Matrix::~Matrix()
{
}