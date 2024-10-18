#include "LinkedList.h"

using namespace std;

// Constructor
template <typename T>
LinkedList<T>::LinkedList()
{
    head = nullptr;
}

template <typename T>
void LinkedList<T>::append(T value)
{
    Node<T> *newNode = new Node<T>();
    newNode->data = value;
    newNode->next = nullptr;

    if (head == nullptr)
    {
        head = newNode;
    }
    else
    {
        Node<T> *temp = head;
        while (temp->next != nullptr)
        {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

template <typename T>
T LinkedList<T>::get(int index)
{
    Node<T> *temp = head;
    int i = 0;
    while (temp != nullptr && i < index)
    {
        temp = temp->next;
        i++;
    }

    if (temp == nullptr)
    {
        cout << "Index out of bounds" << endl;
        return T();
    }

    return temp->data;
}

// Prepend a node at the beginning
template <typename T>
void LinkedList<T>::prepend(T value)
{
    Node<T> *newNode = new Node<T>();
    newNode->data = value;
    newNode->next = head;
    head = newNode;
}

// Delete a node by value (works with any type T that supports comparison)
template <typename T>
void LinkedList<T>::deleteByValue(T value)
{
    if (head == nullptr)
    {
        cout << "List is empty!" << endl;
        return;
    }

    // If the node to be deleted is the head node
    if (head->data == value)
    {
        Node<T> *temp = head;
        head = head->next;
        delete temp;
        return;
    }

    Node<T> *temp = head;
    while (temp->next != nullptr && temp->next->data != value)
    {
        temp = temp->next;
    }

    if (temp->next == nullptr)
    {
        cout << "Value not found in the list!" << endl;
    }
    else
    {
        Node<T> *nodeToDelete = temp->next;
        temp->next = temp->next->next;
        delete nodeToDelete;
    }
}

// Display the list (assumes T supports the << operator)
template <typename T>
void LinkedList<T>::display()
{
    if (head == nullptr)
    {
        cout << "List is empty!" << endl;
        return;
    }

    Node<T> *temp = head;
    while (temp != nullptr)
    {
        cout << temp->data << endl;
        temp = temp->next;
    }
}

// Destructor
template <typename T>
LinkedList<T>::~LinkedList()
{
    while (head != nullptr)
    {
        Node<T> *temp = head;
        head = head->next;
        delete temp;
    }
}
