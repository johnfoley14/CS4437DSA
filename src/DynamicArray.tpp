#include "DynamicArray.h"

template <typename T>
DynamicArray<T>::DynamicArray(int capacity) {
  this->capacity = capacity;
  this->size = 0;
  this->data = new T[capacity];
}

template <typename T>
DynamicArray<T>::~DynamicArray() {
  cout << "deleting array" << endl;
  delete[] data;
}

template <typename T>
void DynamicArray<T>::add(const T& value) {
  if (size >= capacity) {
    resize();
  }
  data[size++] = value;
}

template <typename T>
T DynamicArray<T>::get(int index) {
  if (index < 0 || index >= size) {
    static T defaultValue = T();
    return defaultValue;
  }
  return data[index];
}

template <typename T>
void DynamicArray<T>::insert(int index, const T& value) {
  if (index < 0) {
    throw std::out_of_range("Index cannot be negative");
  }
  if (index >= size) {
    // Auto-resize and fill in gaps with default values if index exceeds current
    // size
    if (index >= capacity) {
      while (index >= capacity) {
        resize();
      }
    }
    for (int i = size; i <= index; ++i) {
      data[i] = T();  // Initialize new elements with default constructor
    }
    size = index + 1;  // Adjust size to include the new index
  }
  data[index] = value;
}

template <typename T>
void DynamicArray<T>::resize() {
  capacity *= 2;
  T* temp = new T[capacity];
  for (int i = 0; i < size; i++) {
    temp[i] = data[i];  // copying
  }
  delete[] data;  // delete old array
  data = temp;
}

template <typename T>
void DynamicArray<T>::printElements() const {
  for (int i = 0; i < size; i++) {
    std::cout << data[i] << std::endl;
  }
  std::cout << std::endl;
}

template <typename T>
int DynamicArray<T>::getSize() const {
  return size;
}

template <typename T>
bool DynamicArray<T>::operator==(const DynamicArray<T>& other) const {
  if (size != other.size) {
    return false;
  }
  for (int i = 0; i < size; i++) {
    if (data[i] != other.data[i]) {
      return false;
    }
  }
  return true;
}

template <typename T>
T& DynamicArray<T>::operator[](int index) {
  if (index < 0) {
    throw std::out_of_range("Index cannot be negative");
  }
  if (index >= size) {
    // Auto-resize and fill in gaps with default values if index exceeds current
    // size
    if (index >= capacity) {
      while (index >= capacity) {
        resize();
      }
    }
    for (int i = size; i <= index; ++i) {
      data[i] = T();  // Initialize new elements with default constructor
    }
    size = index + 1;  // Adjust size to include the new index
  }
  return data[index];
}

template <typename T>
const T& DynamicArray<T>::operator[](int index) const {
  if (index < 0 || index >= size) {
    static T defaultValue = T();
    return defaultValue;
  }
  return data[index];
}
