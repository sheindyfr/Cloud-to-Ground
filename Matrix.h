#pragma once
#include<iostream>
#include<vector>
#define N 100
#define M 100
//--------------------------
class Matrix
{
private:
	float data[N][M];
public:
	Matrix();
	Matrix& setData(std::vector<float> &vData);
	float** getData();
	~Matrix();
};
//--------------------------
