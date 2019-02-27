#pragma once
#include <locale.h>
#include <iostream>
#include "Product.h"
using namespace std;


// ����� ��������� ����������
template <class T2>
class Transaction {
	T2* currentState; // ������� �������� ������� ������
	T2* prevState; // ���������� �������� ������� ������
public:
	Transaction() : prevState(NULL), currentState(new T2) {} // �����������
	Transaction(const Transaction & obj) : currentState(new T2(*(obj.currentState))), prevState(NULL) {}
	~Transaction() {
		delete currentState;
		delete prevState;
	} //����������
	Transaction& operator= (const Transaction & obj); // ������������������ ������������
	void show(); // ����������� ��������� (����������� � ��������)�������
	void beginTransactions(); // ����� ������ ����������
	int setTransactions(Product*);
	void commit(); // ����� ������������� (�������) ����������
	void deleteTransactions(); //����� ������ ����������
	T2* operator->(); // ���������� �������� ->
};

// ���������� ��������� =
template <class T2>
Transaction<T2>& Transaction<T2>::operator=(const Transaction<T2> & obj)
{
	if (this != &obj) // �������� �� ������ obj=obj
	{
		delete currentState; // �������� �������� �������� �������
		currentState = new T2(*(obj.currentState)); // �������� � �����������
	}
	return *this;
}

// ���������� ��������� ->
template <class T2>
T2* Transaction<T2>::operator->()
{
	return currentState;
}

// ����� ����������� ��������� �������
template <class T2>
void Transaction<T2>::show() {
	cout << "��������� ������� ";
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
void Transaction<T2>::beginTransactions() {// ����� ������ ����������
	delete prevState; // �������� ����������� ��������
	prevState = currentState; // ������� ���������� ����������
	currentState = NULL; // �������� ��������� ���
	currentState = new T2(*prevState); // �������� ������ �������� �������� ���������
}

template <class T2>
int Transaction<T2>::setTransactions(Product* products) {
	if (!currentState) return 0; // ������ (���������� �������� ��������)
	currentState->set(products); // ��������� ��������� �������
	return 1; // �������� ��������� ����������
}

template <class T2>
void Transaction<T2>::commit() {// ����� ������������� (�������) ����������
	delete prevState; // �������� ����������� ��������
	prevState = NULL; // ����������� ��������� ���
}

template <class T2>
void Transaction<T2>::deleteTransactions() {//����� ������ ����������
	if (prevState != NULL) {
		delete currentState; // �������� �������� ��������
		currentState = prevState; // ���������� ���������� �������
		prevState = NULL; // ����������� ��������� ���
	}
}

