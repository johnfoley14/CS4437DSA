#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>
#include <string>

// Create LinkedList node where the data is generic
template <typename T>
struct Node
{
    T data;     // Generic data
    Node *next; // Pointer to the next node
};

template <typename T>
class LinkedList
{
public:
    Node<T> *head;
    LinkedList();
    void append(T value);
    void prepend(T value);
    void deleteByValue(T value);
    void display();
    T get(int index);
    ~LinkedList();
};

#include "LinkedList.tpp"

#endif
