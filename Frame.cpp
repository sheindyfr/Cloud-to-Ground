#include "Frame.h"


//----------------------
// default constructor
//---------------------
Frame::Frame()
{
}

//-----------------------------------------------------------
// the ctr update the data and the type by the recive vector
//-----------------------------------------------------------
Frame::Frame(std::vector<float> &vData)
{
	for (int i = 0; i < vData.size() - 1; i++)
		data.push_back(vData[i]);

	// check the last value to figure the frame type
	type = (vData[vData.size() - 1] == 1) ? fullFrame : halfFrame;
}

//--------------------------------------------------------------
// the function figure out the indexes from the vector,
// then, take the last matrix and change the specific locations
//--------------------------------------------------------------
void Frame::figureAndCreateMatrix(Matrix & mat)
{
	int i, indexI, indexJ;
	float value;
	for (i = 0; i < data.size() - 1; i +=2)
	{
		short temp = (short)i;
		indexI = temp >> 8;		// take the most 8 bits
		indexJ = temp & 255;	// take the last 8 bits
		value = data[i + 1];	// the new value to set 
		mat.updateValueByIndex(indexI, indexJ, value);
	}
}

//-----------------------------------------
// change all the matrix (for full frame)
//-----------------------------------------
void Frame::createMatrix(Matrix & mat)
{
	mat.setData(data);
}

//-----------------------------------------
// get the type of the frame (half/full)
//-----------------------------------------
frameType Frame::getType()
{
	return type;
}


Frame::~Frame()
{
}
