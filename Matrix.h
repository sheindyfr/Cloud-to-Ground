#pragma once
#include<iostream>
#include<vector>
#define N 1000
#define M 10
//--------------------------
class Matrix
{
private:
	float data[N][M];
public:
	int rows;
	int columns;
	Matrix();
	void setData(std::vector<float>& vData);
	void updateValueByIndex(int i, int j, float val);
	void printMatrix();
	float getDataByIndex(int i,int j );
	~Matrix();
};
//--------------------------