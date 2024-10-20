#ifndef DYNAMICARRAY_H
#define DYNAMICARRAY_H

#include <iostream> 

template <typename T>
class DynamicArray {
private:
    T* data;
    int size;
    int capacity;

public:
    DynamicArray(int capacity = 1);
    ~DynamicArray();
    void add(const T &value);
    void resize();
    void printElements() const;
};


#endif 
