#pragma once
#include<iostream>
#include<vector>
#include"Matrix.h"

// defined enum for the frame type
enum frameType { halfFrame = 0, fullFrame };

//--------------------------------------------
class Frame
{
private:
	std::vector<float> data;
	frameType type;
public:
	Frame();
	Frame(std::vector<float> &vData);
	void figureAndCreateMatrix(Matrix& mat);
	void createMatrix(Matrix& mat);
	frameType getType();
	~Frame();
};
//--------------------------------------------
