#include "Store.h"


string Store::getStoreName()
{
	return this->storeName;
}

string Store::getStoreType()
{
	return this->storeType;
}

void Store::setStoreName(string name)
{
	this->storeName = name;
}

void Store::setStoreType(string type)
{
	this->storeType = type;
}
