#include "LinkedList.h"

// Constructor
template <typename T>
LinkedList<T>::LinkedList() {
  head = nullptr;
}

// Copy constructor
template <typename T>
LinkedList<T>::LinkedList(const LinkedList<T> &other) {
  if (other.head == nullptr) {
    head = nullptr;  // The other list is empty, so set the head to nullptr
  } else {
    // Create the first node
    head = new Node<T>();
    head->data = other.head->data;

    Node<T> *current = head;             // Pointer to the new list
    Node<T> *otherCurrent = other.head;  // Pointer to the other list

    // Traverse the other list and copy each node
    while (otherCurrent->next != nullptr) {
      otherCurrent = otherCurrent->next;

      Node<T> *newNode = new Node<T>();
      newNode->data = otherCurrent->data;
      newNode->next = nullptr;

      current->next = newNode;
      current = newNode;
    }
  }
}

template <typename T>
void LinkedList<T>::append(T value) {
  Node<T> *newNode = new Node<T>();
  newNode->data = value;
  newNode->next = nullptr;

  if (head == nullptr) {
    head = newNode;
  } else {
    Node<T> *temp = head;
    while (temp->next != nullptr) {
      temp = temp->next;
    }
    temp->next = newNode;
  }
}

template <typename T>
T LinkedList<T>::get(int index) {
  Node<T> *temp = head;
  int i = 0;
  while (temp != nullptr && i < index) {
    temp = temp->next;
    i++;
  }

  if (temp == nullptr) {
    return T();
  }

  return temp->data;
}

template <typename T>
T LinkedList<T>::get(int index) const {
  Node<T> *temp = head;
  int i = 0;
  while (temp != nullptr && i < index) {
    temp = temp->next;
    i++;
  }

  if (temp == nullptr) {
    return T();
  }

  return temp->data;
}

template <typename T>
bool LinkedList<T>::exists(int index) const {
  Node<T> *temp = head;
  int i = 0;
  while (temp != nullptr && i < index) {
    temp = temp->next;
    i++;
  }

  return temp != nullptr;
}

// Prepend a node at the beginning
template <typename T>
void LinkedList<T>::prepend(T value) {
  Node<T> *newNode = new Node<T>();
  newNode->data = value;
  newNode->next = head;
  head = newNode;
}

// Delete a node by value (works with any type T that supports comparison)
template <typename T>
void LinkedList<T>::deleteByValue(T value) {
  if (head == nullptr) {
    cout << "List is empty!" << endl;
    return;
  }

  // If the node to be deleted is the head node
  if (head->data == value) {
    Node<T> *temp = head;
    head = head->next;
    delete temp;
    return;
  }

  Node<T> *temp = head;
  while (temp->next != nullptr && temp->next->data != value) {
    temp = temp->next;
  }

  if (temp->next == nullptr) {
    cout << "Value not found in the list!" << endl;
  } else {
    Node<T> *nodeToDelete = temp->next;
    temp->next = temp->next->next;
    delete nodeToDelete;
  }
}

// Display the list (assumes T supports the << operator)
template <typename T>
void LinkedList<T>::display() {
  if (head == nullptr) {
    cout << "List is empty!" << endl;
    return;
  }

  Node<T> *temp = head;
  while (temp != nullptr) {
    cout << temp->data << endl;
    temp = temp->next;
  }
}

// Destructor
template <typename T>
LinkedList<T>::~LinkedList() {
  while (head != nullptr) {
    Node<T> *temp = head;
    // cout << "Deleting LinkedList Node with value: " << head->data << endl;
    head = head->next;
    delete temp;
  }
}

template <typename T>
bool LinkedList<T>::operator==(const LinkedList<T> &other) const {
  Node<T> *temp1 = head;
  Node<T> *temp2 = other.head;

  while (temp1 != nullptr && temp2 != nullptr) {
    if (temp1->data != temp2->data) {
      return false;
    }
    temp1 = temp1->next;
    temp2 = temp2->next;
  }

  // If one list is longer than the other
  return temp1 == nullptr && temp2 == nullptr;
}

// Iterator dereference operator (return reference to current node data)
template <typename T>
T &LinkedList<T>::Iterator::operator*() {
  return current->data;
}

// Iterator pre-increment operator (move to next node)
template <typename T>
typename LinkedList<T>::Iterator &LinkedList<T>::Iterator::operator++() {
  current = current->next;
  return *this;
}

// Iterator comparison operator (check if two iterators are not equal)
template <typename T>
bool LinkedList<T>::Iterator::operator!=(const Iterator &other) const {
  return current != other.current;
}

// Begin function: returns an iterator to the first node (head)
template <typename T>
typename LinkedList<T>::Iterator LinkedList<T>::begin() {
  return Iterator(head);
}

// End function: returns an iterator to the end (nullptr)
template <typename T>
typename LinkedList<T>::Iterator LinkedList<T>::end() {
  return Iterator(nullptr);
}
