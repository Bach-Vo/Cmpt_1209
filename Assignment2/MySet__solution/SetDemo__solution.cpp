#include <iostream>
#include "MySet.h"

using namespace std;

int main() {
	int list1[20];
	int list2[20];

	cout << "Enter a list of at most 20 integers, enter a non-digit character after the last value: ";
	int size1 = 0;
	while(size1 < 20) {
		int x;
		cin >> x;
		if (cin.fail()) {
			cin.clear();
			cin.ignore();
			break;
		}
		list1[size1++] = x;
	}

	
	cout << "Enter a list of at most 20 integers, enter a non-digit character after the last value: ";
	int size2 = 0;
	while(size2 < 20) {
		int x;
		cin >> x;
		if (cin.fail()) {
			cin.clear();
			cin.ignore();
			break;
		}
		list2[size2++] = x;
	}

	MySet set1(list1, size1);
	MySet set2(list2, size2);

	cout << "The union of the sets is: ";
	set1.unionWith(set2).print();

	cout << "The intersection of the sets is: ";
	set1.intersectWith(set2).print();

	return 0;
}