#include "MinHeap.h"

// Constructor with capacity since we know we only need to store the top 50 books
MinHeap::MinHeap(int capacity)
{
    this->capacity = capacity;
    heapSize = 0;
    heapArray = new BookScore[capacity];
}

// Destructor to free the allocated memory
MinHeap::~MinHeap()
{
    delete[] heapArray;
}

int MinHeap::parent(int i)
{
    return (i - 1) / 2;
}

int MinHeap::left(int i)
{
    return (2 * i + 1);
}

int MinHeap::right(int i)
{
    return (2 * i + 2);
}

void MinHeap::percolateUp(int i)
{
    int current = i;
    // While the current node is not the root and its score is smaller than its parent
    while (current != 0 && heapArray[current] < heapArray[parent(current)])
    {
        // Swap the current node with its parent
        std::swap(heapArray[current], heapArray[parent(current)]);
        // Move the current index to its parent index
        current = parent(current);
    }
}

void MinHeap::percolateDown(int i)
{
    int smallest = i;
    int l = left(i);
    int r = right(i);

    // If the left child exists and has a smaller score than the current smallest
    if (l < heapSize && heapArray[l] < heapArray[smallest])
        smallest = l;

    // If the right child exists and has a smaller score than the current smallest
    if (r < heapSize && heapArray[r] < heapArray[smallest])
        smallest = r;

    // If the smallest is not the current node, swap and percolate down
    if (smallest != i)
    {
        std::swap(heapArray[i], heapArray[smallest]);
        percolateDown(smallest); // Recursively percolate down the affected subtree
    }
}

// Function to insert a new BookScore into the heap
void MinHeap::insert(const BookScore &book)
{
    if (heapSize == capacity)
    {
        std::cout << "Overflow: Could not insert key\n";
        return;
    }

    // Insert the new BookScore at the end of the heap
    heapSize++;
    int i = heapSize - 1;
    heapArray[i] = book;

    // Percolate up to restore the heap property
    percolateUp(i);
}

// Function to extract the root (minimum element)
BookScore MinHeap::extractMin()
{
    if (heapSize <= 0)
    {
        std::cerr << "Heap is empty\n";
        return {-1, -1.0f};
    }

    if (heapSize == 1)
    {
        heapSize--;
        return heapArray[0];
    }

    // Store the minimum value (root) and move the last element to the root
    BookScore root = heapArray[0];
    heapArray[0] = heapArray[heapSize - 1];
    heapSize--;

    // Percolate down to restore the heap property
    percolateDown(0);

    return root;
}

// Function to get the minimum element without removing it (were going to use this to check if we have a bigger score to insert)
BookScore MinHeap::getMin() const
{
    if (heapSize <= 0)
    {
        std::cerr << "Heap is empty\n";
        return {-1, -1.0f}; // Return an invalid BookScore if the heap is empty
    }

    return heapArray[0];
}

// for debugging purposes
void MinHeap::printHeap() const
{
    for (int i = 0; i < heapSize; i++)
    {
        std::cout << "ID: " << heapArray[i].id << ", Score: " << heapArray[i].score << std::endl;
    }
}
