#include <iostream>
#include "MySet.h"
using namespace std;

/* int getSize();
void print();
bool add(int item);
bool add(const int sequence[], int size);
bool remove(int item);
void clear(); */

int main(){
    const int size1 = 3;
    const int size2 = 4;
    int sequence1[size1] = {1, 2, 3};
    int sequence2[size2] = {3, 4, 5, 3};
    MySet set1;

cout << "set1: " << endl;
    set1.add(sequence1, size1);
cout << "set2: " << endl;
    MySet set2(sequence2, size1);

cout << "unionWith:" << endl;
    set1.intersectWith(set2).print();
cout << "intersecWith: " << endl;
    set1.intersectWith(set2).print();
return 0;
}