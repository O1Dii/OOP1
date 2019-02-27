#pragma once
#include <iostream>
#include <locale.h>
#include "Product.h"
using namespace std;

template <class T>
struct Status {
	T *RealPtr; // ���������
	int counter; // ������� ����� ������ �� ������
};

template <class T>
class smartPointer {
	Status<T> *StatPtr;
public:
	smartPointer(T *ptr = 0);
	smartPointer(const smartPointer &);
	~smartPointer();
	smartPointer &operator=(const smartPointer &); // ���������� ��������� =
	T * operator->() const; // ���������� ��������� ->
};

template <class T>
smartPointer<T>::smartPointer(T *ptr) {
	if (!ptr) StatPtr = NULL; // ��������� �� ������ ������
	else {
		StatPtr = new Status<T>;
		StatPtr->RealPtr = ptr; // �������������� ������ ����������
		StatPtr->counter = 1; // ������� ��������������� ��������
	}
}

template <class T>
smartPointer<T>::smartPointer(const smartPointer &p) :StatPtr(p.StatPtr)
{
	if (StatPtr) StatPtr->counter++; // ������ ���������� ����� ������
}

template <class T>
smartPointer<T>::~smartPointer() {
	if (StatPtr) {
		StatPtr->counter--; // ����������� ����� ������ �� ������
		if (StatPtr->counter <= 0) { // ���� ����� ������ �� ������ ������ ���� ����� ����, �� ������������ ������
			delete StatPtr->RealPtr;//������ �� ������ ������������
			delete StatPtr;
		}
	}
}

template <class T>
T *smartPointer<T>::operator->() const {
	if (StatPtr) return StatPtr->RealPtr;
	else return NULL;
}

template <class T>
smartPointer<T> &smartPointer<T>::operator=(const smartPointer &p) {
	if (StatPtr) {
		StatPtr->counter--; // ��������� ������� ��������������� ��������
		if (StatPtr->counter <= 0) { // ���� �������� ���, �� ����������� ������������� ���������� ������
			delete StatPtr->RealPtr;
			delete StatPtr;
		}
	}
	StatPtr = p.StatPtr; // ������������� � ������ ���������
	if (StatPtr) StatPtr->counter++; // ��������� ������� ��������������� ��������
	return *this;
}