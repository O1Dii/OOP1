#pragma once
#include <locale.h>
#include <iostream>
#include "Product.h"
using namespace std;


// класс поддержки транзакций
template <class T2>
class Transaction {
	T2* currentState; // текущее значение объекта класса
	T2* prevState; // предыдущее значение объекта класса
public:
	Transaction() : prevState(NULL), currentState(new T2) {} // конструктор
	Transaction(const Transaction & obj) : currentState(new T2(*(obj.currentState))), prevState(NULL) {}
	~Transaction() {
		delete currentState;
		delete prevState;
	} //деструктор
	Transaction& operator= (const Transaction & obj); // перегрузкаоперации присваивания
	void show(); // отображение состояний (предыдущего и текущего)объекта
	void beginTransactions(); // метод начала транзакции
	int setTransactions(Product*);
	void commit(); // метод подтветждения (коммита) транзакции
	void deleteTransactions(); //метод отката транзакции
	T2* operator->(); // перегрузка операции ->
};

// перегрузка оператора =
template <class T2>
Transaction<T2>& Transaction<T2>::operator=(const Transaction<T2> & obj)
{
	if (this != &obj) // проверка на случай obj=obj
	{
		delete currentState; // удаление текущего значения объекта
		currentState = new T2(*(obj.currentState)); // создание и копирование
	}
	return *this;
}

// перегрузка оператора ->
template <class T2>
T2* Transaction<T2>::operator->()
{
	return currentState;
}

// метод отображения состояния объекта
template <class T2>
void Transaction<T2>::show() {
	cout << "состояния объекта ";
	if (prevState) {
		cout << "prevState = ";
		prevState->show();
	}
	else {
		cout << "prevState = NULL" << endl;
	}
	if (currentState) {
		cout << "currentState = ";
		currentState->show();
	}
	else {
		cout << "currentState = NULL" << endl;
	}
}

template <class T2>
void Transaction<T2>::beginTransactions() {// метод начала транзакции
	delete prevState; // удаление предыдущего значения
	prevState = currentState; // текущее становится предыдущим
	currentState = NULL; // текущего состояния нет
	currentState = new T2(*prevState); // создание нового значения текущего состояния
}

template <class T2>
int Transaction<T2>::setTransactions(Product* products) {
	if (!currentState) return 0; // ошибка (необходимо отменить действие)
	currentState->set(products); // изменение состояния объекта
	return 1; // успешное окончание транзакции
}

template <class T2>
void Transaction<T2>::commit() {// метод подтветждения (коммита) транзакции
	delete prevState; // удаление предыдущего значения
	prevState = NULL; // предыдущего состояния нет
}

template <class T2>
void Transaction<T2>::deleteTransactions() {//метод отката транзакции
	if (prevState != NULL) {
		delete currentState; // удаление текущего значения
		currentState = prevState; // предыдущее становится текущим
		prevState = NULL; // предыдущего состояния нет
	}
}

