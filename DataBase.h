#include "Matrix.h"
using namespace std;


class DataBase{
private:
	 string fileName;
	

public:
    DataBase(string name);
	int updateMatrix(Matrix &mat);
	string getFile();
	~DataBase();
};