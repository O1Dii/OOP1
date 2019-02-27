#pragma once
#include <string>
#include "Store.h"

class Product : public Store
{
private:
	string productName;
	string manufacturer;
	int price;
public:
	string getProductName();
	string getManufacturer();
	int getPrice();
	void setProductName(string);
	void setManufacturer(string);
	void setPrice(int);
};

