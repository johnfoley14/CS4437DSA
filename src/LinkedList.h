#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>
#include <string>
using namespace std;

// Create LinkedList node where the data is generic
template <typename T>
struct Node {
  T data;      // Generic data
  Node *next;  // Pointer to the next node
};

template <typename T>
class LinkedList {
 public:
  Node<T> *head;
  LinkedList();
  void append(T value);
  void prepend(T value);
  void deleteByValue(T value);
  void display();
  T get(int index);

  bool operator==(const LinkedList<T> &other) const;

  // Iterator class definition
  class Iterator {
   private:
    Node<T> *current;

   public:
    Iterator(Node<T> *node)
        : current(node) {}   // Constructor to initialize with a node
    T &operator*();          // Dereference operator
    Iterator &operator++();  // Pre-increment operator
    bool operator!=(const Iterator &other) const;  // Comparison operator
  };

  Iterator begin();  // Return an iterator to the first element
  Iterator end();

  ~LinkedList();
};

#include "LinkedList.tpp"

#endif
