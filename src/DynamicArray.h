#ifndef DYNAMICARRAY_H
#define DYNAMICARRAY_H

#include <iostream>

using namespace std;

template <typename T>
class DynamicArray
{
private:
    T *data;
    int size;
    int capacity;

public:
    DynamicArray(int capacity = 1000000);
    ~DynamicArray();
    void add(const T &value);
    T get(int index);
    void insert(int index, const T &value);
    void resize();
    void printElements(int start = 0, int end = 10) const;
    int getSize() const;
    bool operator==(const DynamicArray<T> &other) const;
    T &operator[](int index);
    const T &operator[](int index) const;
};

#include "DynamicArray.tpp"

#endif
