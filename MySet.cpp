#include "MySet.h"
#include <iostream>
using namespace std;
//1) A no-arg constructor that creates an empty set with the buffer size of 10.
MySet::MySet(){
    size = 0;
    bufferSize = 10;
    set = new int [bufferSize];
}
//2) A parameterized constructor with two input parameters: an array of integers and the size of the array. This method creates a set including the distinct integers in the input array. The buffer size in this case is identified as described for adding more than one value to the set.
MySet::MySet(const int sequence[], int size){
    bufferSize = size;
    this->size = 0;
    set = new int [bufferSize];
    for (int i = 0; i < size; i++)
    {
        if (!has(sequence[i]))
        {
            add(sequence[i]);
        }
    }
}
//3) A copy constructor that creates a MySet object using an existing MySet object.
MySet::MySet(const MySet& anotherSet){
    cout << "\tCopy Constructor Called" << endl;          //_test
    bufferSize = anotherSet.bufferSize;
    size = anotherSet.size;
    this->set = new int [bufferSize];
    for (int i = 0; i < size; i++)
    {   set[i] = anotherSet.set[i];  }
}
//4)Destructor
MySet::~MySet(){
    cout << "Destructor is called" << endl;            //_test
    delete [] set;
}
//5) The "add" method that accepts an integer as its input parameter and if the input value does not exist in the set, adds it to the set and returns true; Otherwise, it returns false and of course the value is not added to the set.
bool MySet::add(int item){
    if(has(item))               //check if item is already in Set[]
        return false;

    if (size == bufferSize)     //double bufferSize if needed
    {
        cout << "bufferSize was doubled" << endl;
        bufferSize *= 2;
        int *tempSet = new int [bufferSize];
        for (int x = 0; x < size; x++)
            tempSet[x] = set[x];
        delete [] set;
        set = tempSet;
    }
    
    set[size++] = item;
    cout << "   added:" << item << endl;
return true;
}
//6) Overload the "add" function to all the distinct values of an array of integers to the set.
bool MySet::add(const int sequence[], int size){
    bool flag = false;  //if added atleast one item of seq, flag is true. None of items in seq went thro, returns false
    //iterating through seq and add items to set[]. Repeated items will be checked and decided in add()
    for (int i = 0; i < size; i++)
    {
        add(sequence[i]);
        flag = true;
    }
return flag;
}
//7) Accepts an integer as its input parameter and if the input value exists in the set, it is removed from the set, and the function returns true; otherwise, it returns false.
bool MySet::remove(int item){
    for (int i = 0; i < size; i++)
    {
        //check if item is in set
        if (item == set[i])     //Cannot use "has()" because tho, can know if item is in set. We are NOT able to know exactly where
        {
            set[i] = set[--size];
        return true;
        }
    }
return false;
}

//8) checks if the input parameter exists in the set. This method returns true if the input value is a member of the set and returns false otherwise.
bool MySet::has(int item) const{
    for (int i = 0; i < size; i++)
    {
        if (item == set[i])
            return true;
    }
return false;
}

//9) creates and returns a new MySet object including all the integers of the current set and another set passed as function's input parameter.
MySet MySet::unionWith(const MySet& anotherSet) const{
    //if(anotherSet.size == 0){/*throw ex*/}
    MySet resultSet(*this);
    for (int i = 0; i < anotherSet.size; i++)
        resultSet.add(anotherSet.set[i]);
return resultSet;
}
//10) The "intersectWith" method creates and returns the intersection of the set with another set passed in the function's input parameter.
MySet MySet::intersectWith(const MySet& anotherSet) const{
    MySet resultSet;
    for (int i = 0; i < size; i++)
    {
        if (has(anotherSet.set[i]))
        {
            resultSet.add(anotherSet.set[i]);
        }
    }
return resultSet;
}
//11) The "clear" method clears the set; empties the set and reset is to its initial state.
void MySet::clear(){
    delete [] set;
    size = 0;
    set = new int [size];
    bufferSize = 10;
}
//12) The "getSize" method returns the number of items included in the set.
int MySet::getSize() const{
    return size;
}
//13) The "print" method displays the set on the screen.
void MySet::print() const{
    cout << "\nPrinting..." << endl;
    for (int i = 0; i < size; i++)
    {
        cout << "\ti_" << i << ": " << set[i] << endl;
    }
}





