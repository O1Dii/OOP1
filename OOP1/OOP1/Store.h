#pragma once
#include <string>
using namespace std;

class Store
{
private:
	string storeName;
	string storeType;
public:
	string getStoreName();
	string getStoreType();
	void setStoreName(string);
	void setStoreType(string);
};

