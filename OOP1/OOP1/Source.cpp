#include "Transaction.h"
#include "Basket.h"

#define SIZE 4

void menu(Product * products) {
	char choice, productsSizeString[10], tempChoice;
	int productsNum[100], numInProductsNum = 0;
	int i = 0, j = 0;
	for (i = 0; i < 100; i++) {
		productsNum[i] = 0;
	}
	Transaction<Basket> firstTransaction;
	firstTransaction->set(NULL);
	do {
		cout << "1. Добавить продукт в корзину" << endl;
		cout << "2. Удалить продукт из корзины" << endl;
		cout << "3. Подтвердить покупку" << endl;
		cout << "4. Отмена покупки" << endl;
		cout << "5. Вывести результат транзакции" << endl;
		cout << "6. Выход" << endl;
		do {
			cin >> choice;
		} while (choice < '1' || choice > '6');
		switch (choice) {
		case '1':
			if (numInProductsNum == 99) {
				cout << "Слишком много продуктов" << endl;
				break;
			}
			for (i = 0; i < SIZE; i++) {
				cout << "Продукт №" << i + 1 << endl;
				cout << products[i].getProductName() << '\n' << products[i].getManufacturer() << '\n' << products[i].getPrice() << '\n' << endl;
			}
			_itoa_s(SIZE, productsSizeString, 10, 10);
			do {
				cin >> tempChoice;
			} while (tempChoice < '1' || tempChoice > productsSizeString[0]);
			productsNum[numInProductsNum] = atoi(&tempChoice);
			break;
		case '2':
			for (i = 0; productsNum[i]; i++) {
				cout << "Продукт №" << i + 1 << endl;
				cout << products[productsNum[i]].getProductName() << '\n' << products[productsNum[i]].getManufacturer() << '\n' << products[productsNum[i]].getPrice() << '\n' << endl;
			}
			_itoa_s(i, productsSizeString, 10, 10);
			do {
				cin >> tempChoice;
			} while (tempChoice < '1' || tempChoice > productsSizeString[0]);
			j = atoi(&tempChoice);
			productsNum[j] = 0;
			while (j < i) {
				productsNum[j] = productsNum[j + 1];
				j++;
			}
			numInProductsNum--;
			break;
		case '3': {
			firstTransaction.beginTransactions();
			Product *tempProductList = new Product[numInProductsNum];
			for (i = 0; i < numInProductsNum; i++) {
				tempProductList[i] = products[productsNum[i]];
			}
			if (firstTransaction.setTransactions(tempProductList)) {
				firstTransaction.commit();
			}
			break;
		}
		case '4':
			firstTransaction.deleteTransactions();
			break;
		case '5':
			firstTransaction.show();
			break;
		case '6':
			exit(0);
			break;
		}
	} while (choice != '6');
}

int main() {
	setlocale(LC_ALL, "Russian");
	Product products[SIZE];
	products[0].setProductName("Макароны");
	products[0].setManufacturer("Боримак");
	products[0].setPrice(20);
	products[1].setProductName("Рис");
	products[1].setManufacturer("Екатеринодар-агро");
	products[1].setPrice(30);
	products[2].setProductName("Колбаса");
	products[2].setManufacturer("Волковыский мясокомбинат");
	products[2].setPrice(50);
	products[3].setProductName("Роллтон");
	products[3].setManufacturer("Маревен Фуд Сэнтрал");
	products[3].setPrice(15);
	menu(products);
}
