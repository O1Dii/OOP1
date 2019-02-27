#pragma once
#include <iostream>
#include <locale.h>
#include "Product.h"
using namespace std;

template <class T>
struct Status {
	T *RealPtr; // указатель
	int counter; // счетчик числа ссылок на объект
};

template <class T>
class smartPointer {
	Status<T> *StatPtr;
public:
	smartPointer(T *ptr = 0);
	smartPointer(const smartPointer &);
	~smartPointer();
	smartPointer &operator=(const smartPointer &); // перегрузка оператора =
	T * operator->() const; // перегрузка оператора ->
};

template <class T>
smartPointer<T>::smartPointer(T *ptr) {
	if (!ptr) StatPtr = NULL; // указатель на объект пустой
	else {
		StatPtr = new Status<T>;
		StatPtr->RealPtr = ptr; // инициализирует объект указателем
		StatPtr->counter = 1; // счетчик «прикрепленных» объектов
	}
}

template <class T>
smartPointer<T>::smartPointer(const smartPointer &p) :StatPtr(p.StatPtr)
{
	if (StatPtr) StatPtr->counter++; // только увеличение числа ссылок
}

template <class T>
smartPointer<T>::~smartPointer() {
	if (StatPtr) {
		StatPtr->counter--; // уменьшается число ссылок на объект
		if (StatPtr->counter <= 0) { // если число ссылок на объект меньше либо равно нулю, то уничтожается объект
			delete StatPtr->RealPtr;//ссылка на объект уничтожается
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
		StatPtr->counter--; // уменьшаем счетчик «прикрепленных» объектов
		if (StatPtr->counter <= 0) { // если объектов нет, то выполняется освобождается выделенная память
			delete StatPtr->RealPtr;
			delete StatPtr;
		}
	}
	StatPtr = p.StatPtr; // присоединение к новому указателю
	if (StatPtr) StatPtr->counter++; // увеличить счетчик «прикрепленных» объектов
	return *this;
}