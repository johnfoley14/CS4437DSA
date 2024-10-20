#include "DynamicArray.h"

template <typename T>
DynamicArray<T>::DynamicArray(int capacity) {
    this->capacity = capacity;
    this->size = 0;
    this->data = new T[capacity];
}


template <typename T>
DynamicArray<T>::~DynamicArray() {
    delete[] data; 
}


template <typename T>
void DynamicArray<T>::add(const T &value) {
    if (size >= capacity) {
        resize();
    }
    data[size++] = value; 
}


template <typename T>
void DynamicArray<T>::resize() {
    capacity *= 2; 
    T* temp = new T[capacity]; 
    for (int i = 0; i < size; i++) {
        temp[i] = data[i]; // copying
    }
    delete[] data; // delete old array
    data = temp; 
}

template <typename T>
void DynamicArray<T>::printElements() const {
    for (int i = 0; i < size; i++) {
        std::cout << data[i] << " ";
    }
    std::cout << std::endl;
}


