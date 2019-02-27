#include "Basket.h"


void Basket::show()
{
	for (int i = 0; i < count; i++)
		std::cout << this->products[i].getProductName() << std::endl;
}

void Basket::set(Product * prod)
{
	this->count = sizeof(prod);
	products = prod;
}

Product * Basket::get()
{
	return products;
}

int Basket::getCount()
{
	return this->count;
}
