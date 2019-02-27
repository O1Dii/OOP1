#include "Product.h"


string Product::getProductName()
{
	return this->productName;
}

string Product::getManufacturer()
{
	return this->manufacturer;
}

int Product::getPrice()
{
	return this->price;
}

void Product::setProductName(string name)
{
	this->productName = name;
}

void Product::setManufacturer(string man)
{
	this->manufacturer = man;
}

void Product::setPrice(int p)
{
	this->price = p;
}
