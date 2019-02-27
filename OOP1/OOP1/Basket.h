#pragma once
#include <iostream>
#include <string>
#include <list>
#include "Store.h"
#include "Product.h"

class Basket : public Store
{
private:
	int sum;
	int count;
	Product *products;
public:
	void show();
	void set(Product *);
	Product* get();
	int getCount();
};