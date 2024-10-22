#ifndef MINHEAP_H
#define MINHEAP_H

#include <iostream>

struct BookScore
{
    int id;
    float score;

    // Overloading the less-than operator to compare scores
    bool operator<(const BookScore &other) const
    {
        return score < other.score;
    }
};

class MinHeap
{
private:
    BookScore *heapArray;
    int capacity; // Maximum possible size of the heap

    // Helper functions to get the index of parent and children
    int parent(int i);
    int left(int i);
    int right(int i);

    // Percolate up: for when we insert a new element so that the heap property is maintained
    void percolateUp(int i);

    // Percolate down: so when we remove the root, we maintain the heap property by moving the last element to the root
    void percolateDown(int i);

public:
    int heapSize; // Current number of elements in the heap

    MinHeap(int capacity);

    // Destructor to free allocated memory
    ~MinHeap();

    // Function to insert a new BookScore into the heap
    void insert(const BookScore &book);

    BookScore extractMin();

    BookScore getMin() const;

    void printHeap() const;
};

#endif
