#ifndef QUEUE_H
#define QUEUE_H

#include<stdexcept>
#include<ostream>
//https://en.cppreference.com/w/cpp/language/friend //" The name of the class that is used in this friend declaration does not need to be previously declared."


/*A Queue is an ordered sequence of items with FIFO characteristic: First In First Out. In other words, the items in a queue are removed in the order that they were inserted in the queue. Queues can be implemented in different ways. A very simple, but inefficient, implementation is to store the items of the queue in an array where the front of the queue is always at index 0 of the array and the new items are always added to the end of the array. 
For example, if the queue is at the beginning empty, and values 5, 3, 9, and 3 are inserted into the queue, respectively, the first remove, removes 5 and all the values 3, 9, and 3 are shifted to the start of the array so 3 (the front of the queue) is placed at index 0.
- You are to implement this class template using dynamic memory allocation. Complete the class template declared in the attached header file as described below: 

1. Add the implementation of the declared methods to the file (out of the class declaration, but in the same file).
2. Implement a copy constructor and a destructor for the class template.
Overload the assignment operator.
Overload the addition operator to merge two queues into a new queue.
Overload the "+=" operator to add a single item to the end of the queue.
Overload the "--" operator to remove the item at the front of the queue.
Overload the equality and inequality operator to compare two queue objects. Two queue objects are equal if their length is equal and all of their corresponding items are equal.
Overload the stream insertion operator (<<) to insert all the items of the queue to an output stream
*/

template <typename T, int capacity> // T is the generic type used for the items in the queue and capacity is the initial size of the queue
class Queue {
public:
	Queue(); // Creates an empty Queue object with the maximum size of "capacity"
    Queue(const Queue& anotherQ);
    ~Queue();   //destructor

    //Overloading operators
    Queue<T,capacity>& operator= (const Queue<T,capacity>& anotherQ);
    Queue<T,capacity>  operator+= (const Queue<T,capacity>& item);
    Queue<T,capacity>  operator-- ();
    

//free func
template<typename U, int capacity>
    friend Queue<U,capacity>& operator+ (const Queue<U,capacity>&, const Queue<U,capacity>&);
    
template<class Queue> friend bool operator== (const Queue<T,capacity>& Q1, const Queue<T,capacity>& Q2); 
template<class Queue> friend bool operator!= (const Queue<T,capacity>& Q1, const Queue<T,capacity>& Q2); 

template<typename U,int capacity>    
    friend ostream& operator<< (ostream&, const Queue<U,capacity>&);


//basic func
	void insert(const T& x); // Inserts x at the end of the queue; if required the queue is expanded (doubled)
	T remove(); // Removes and returns the first item of the queue (i.e. item at index 0), or throws an exception if the queue is empty,
	bool empty() const; // Returns true if the queue is empty, or false otherwise.
	int getSize() const; // Returns the number of items in the queue.
private:
	T* q; // q points to the front of the queue in the heap
	int size; // size is the number of items in the queue
	int maxSize; // maxSize is the maximum size of the array pointed by q.
};
#endif
//constructor
template<typename T, int capacity>
Queue<T,capacity>::Queue()
{
    size = 0;
    maxSize = capacity;
    q = nullptr;
}
//copy constructor
template<typename T, int capacity>
Queue<T, capacity>::Queue(const Queue& anotherQ)
{
    size = anotherQ.size;
    maxSize = anotherQ.maxSize;
    q = new T [maxSize];
    for (int i = 0; i < size; i++)
        q[i] = anotherQ.q[i];
}
//destructor
template<typename T, int capacity>
Queue<T, capacity>::~Queue()
{
    delete [] q;
}



//   =   //overload assignment
template<typename T, int capacity>
Queue<T,capacity>& Queue<T,capacity>::operator= (const Queue<T, capacity>& anotherQ)
{
    if(&this != anotherQ)   //self-assignment check
    {
        delete [] q; 
        q = nullptr;   

        size = anotherQ.size;
        maxSize = anotherQ.maxSize;
        q = new T [maxSize];
        for (int i = 0; i < size; i++)
            q[i] = anotherQ.q[i];
    }
return *this;
}
//  +  //overlead addition; merge two queues into a new queue
/*??? how should the priority of the resultQ be decided. 
Expecting a new arr or a new obj ??? */
template<typename T, int capacity>
Queue<T,capacity>& Queue<T,capacity>::operator+ (const Queue<T,capacity>& Q1, const Queue<T,capacity>& Q2)
{
    if (Q1.empty() and Q2.empty())
        resultQ = new T [0];
    else if (Q1.empty())
        resultQ = new T [Q2.maxSize];
    else if (Q2.empty())
        resultQ = new T [Q1.maxSize];
    else
    {
        resultQ = new T [Q1.size + Q2.size];
        for (int i = 0; i < Q1.size; i++)
            resultQ[i] = Q1.q[i];

        for (int i = 0; i < Q2.size; i++)
            resultQ[i] = Q2.q[i];
    }
return resultQ;
}


//   +=   //overload += to add a single item to the end of the queue
template<typename T, int capacity>
Queue<T,capacity> Queue<T,capacity>::operator+= (const Queue<T, capacity>& item)
{
    insert(item);
    return q;
}

//   --   //overload -- to remove the item at the front of the queue
template<typename T, int capacity>
Queue<T,capacity> Queue<T,capacity>::operator-- ()
{
    remove();
    return q;
}

/*IF:
- length(a) == length(b)
- a[i] == b[i]
*/
//   ==   //
template<typename U, int capacity>
bool Queue<U,capacity>::operator== (const Queue<U,capacity>& Q1, const Queue<U,capacity>& Q2)
{
    if(Q1.size == Q2.size){
        for (int i = 0; i <= Q1.size; i++)
        {
            if(Q1.q[i] != Q2.q[i]){
                return false;
            }
        }
        
    }
return true;
}

//   !=   //
template<typename U, int capacity>
bool Queue<U,capacity>::operator!= (const Queue<U,capacity>& Q1, const Queue<U,capacity>& Q2)
{
    if(Q1 == Q2){
        return false;
    }
return true;
}


//   <<   //overload << to insert all the items of the queue to an ouput stream
template<typename U, int capacity>
ostream& operator<< (ostream& out, const Queue<U,capacity>& anotherQ)
{
    for (int i = 0; i < anotherQ.size; i++)
    {
        out << anotherQ.q[i];
    }
return out;
}


//basic func
template<typename T, int capacity>
void Queue<T, capacity>::insert(const T& x)
{
    if (size == maxSize)
    {
        maxSize *= 2;
        T* tempQ = new T [maxSize];

        for (int i = 0; i <= size; i++)
            tempQ[i] = q[i];

        delete [] q;
        q = tempQ;
    }
    q[size++] = x;
    size++;
}

template<typename T, int capacity>
T Queue<T, capacity>::remove()
{
    if(empty())
       throw runtime_error("Queue is empty");

    T deletedItem = q[0];  //assign the top item(to be deleted item) to a placehoder "deletedItem"
    for (int i = 0; i < (size-1); i++)
    {
        q[i] = q[i+1];//shifting back 1 item 
    }
    size--;     //resizing queue
return deletedItem;
}

template<typename T, int capacity>
bool Queue<T, capacity>::empty() const
{
    if (size == 0)
        return true;
    return false;
}

template<typename T, int capacity>
int Queue<T, capacity>::getSize() const
{
    return size;
}