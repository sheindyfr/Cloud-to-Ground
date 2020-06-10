#include "Matrix.h"

//-----------------------------------------
// default constructor
//-----------------------------------------
Matrix::Matrix()
{
}
//-----------------------------------------
// the function set the Matrix
//-----------------------------------------
Matrix& Matrix::setData(std::vector<float> &vData)
{
	int i, j, k = 0;
	for (i = 0; i < N; ++i)
	{
		for (j = 0; j < M; ++j)
		{
			data[i][j] = vData[k];
		}
	}
}
//-----------------------------------------
// the function return the Matrix
//-----------------------------------------
float** Matrix::getData()
{
	return (float**)data;
}
//-----------------------------------------
Matrix::~Matrix()
{
}
