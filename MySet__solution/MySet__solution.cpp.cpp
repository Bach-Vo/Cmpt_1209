#include <iostream>
#include "MySet.h"
using namespace std;

MySet::MySet() {
	bufferSize = 10;
	size = 0;
	set = new int[bufferSize];
}

MySet::MySet(const int sequence[], int size) {
	this->size = 0;
	bufferSize = size;
	set = new int[bufferSize];
	
	for (int i = 0; i < size; i++) {
		add(sequence[i]);
	}
}

MySet::MySet(const MySet& anotherSet) {
	size = anotherSet.size;
	bufferSize = anotherSet.bufferSize;
	set = new int[bufferSize];

	for (int i = 0; i < size; i++)
		set[i] = anotherSet.set[i];
}

MySet::~MySet() {
	delete[] set;
}

bool MySet::add(int item) {
	if (has(item))
		return false;

	if (size == bufferSize) {
		bufferSize *= 1.5;
		int* temp = new int[bufferSize];
		for (int i = 0; i < size; i++)
			temp[i] = set[i];
		delete[] set;
		set = temp;
	}

	set[size++] = item;
	return true;
}

bool MySet::add(const int sequence[], int size) {
	bool updated = false;
	for (int i = 0; i < size; i++) {
		if (add(sequence[i]))
			updated = true;
	}

	return updated;
}

bool MySet::remove(int item) {
	for (int i = 0; i < size; i++) 
		if (set[i] == item){
			set[i] = set[--size];
			return true;
		}
	
	return false;
}

bool MySet::has(int item) const {
	for (int i = 0; i < size; ++i) {
		if (item == set[i])
			return true;
	}
	return false;
}

MySet MySet::unionWith(const MySet& anotherSet) const {
	MySet newSet(*this);
	for (int i = 0; i < anotherSet.size; i++) {
		newSet.add(anotherSet.set[i]);
	}
	
	return newSet;
}

MySet MySet::intersectWith(const MySet& anotherSet) const {
	MySet newSet;
	for (int i = 0; i < size; i++) {
		if(anotherSet.has(set[i]))
			newSet.add(set[i]);
		
	}

	return newSet;
}

void MySet::clear() {
	bufferSize = 10;
	size = 0;
	delete[] set;
	set = new int[bufferSize];
}

int MySet::getSize() const {
	return size;
}

void MySet::print() const {
	for (int i = 0; i < size; i++)
		cout << set[i] << ' ';
}