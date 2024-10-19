#ifndef BookInfo_H
#define BookInfo_H

#include "LinkedList.h" // Include the LinkedList template class

using namespace std;

// WordInfo structure
struct WordInfo
{
    int *positions; // Dynamic array of positions (size is equal to count)
    int count;      // Number of occurrences (also the size of positions array)
    float score;    // precomputed score for this word

    friend ostream &operator<<(ostream &os, const WordInfo &wi)
    {
        os << "Word count: " << wi.count << ", Score: " << wi.score; // Customize as needed

        if (wi.count > 0)
        {
            os << ", Positions: [";
            for (int i = 0; i < wi.count; ++i)
            {
                os << wi.positions[i];
                if (i < wi.count - 1)
                    os << ", ";
            }
            os << "]";
        }
        return os;
    }
    // Constructor
    WordInfo(int cnt = 0, float scr = 0.0, int *pos = nullptr)
        : count(cnt), score(scr)
    {
        if (count > 0)
        {
            positions = new int[count];
            for (int i = 0; i < count; ++i)
            {
                positions[i] = pos[i]; // Copy the array elements
            }
        }
        else
        {
            positions = nullptr;
        }
    }

    // Destructor
    ~WordInfo()
    {
        delete[] positions; // Free dynamically allocated memory
    }

    // Copy constructor (for deep copy)
    WordInfo(const WordInfo &other)
    {
        count = other.count;
        score = other.score;

        if (count > 0)
        {
            positions = new int[count];
            for (int i = 0; i < count; ++i)
            {
                positions[i] = other.positions[i]; // Copy the array
            }
        }
        else
        {
            positions = nullptr;
        }
    }

    WordInfo &operator=(const WordInfo &other)
    {
        if (this == &other)
            return *this;

        delete[] positions; // Free existing memory

        count = other.count;
        score = other.score;

        if (count > 0)
        {
            positions = new int[count];
            for (int i = 0; i < count; ++i)
            {
                positions[i] = other.positions[i]; // Copy the array elements
            }
        }
        else
        {
            positions = nullptr;
        }

        return *this;
    }
};

// BookInfo structure
// This structure will be passed into our ranking function to calculate the score for a file based on the search query
// For example if the search is "tall crazy cow", then BookInfo will have WordInfo objects if this file contains any of these words
struct BookInfo
{
    int fileId;                 // Unique ID for the file
    int totalWords;             // Total number of words in the file
    LinkedList<WordInfo> words; // LinkedList of WordInfo for each word searched for. Each node will include data of the word information for this file

    BookInfo(int id = 0, int total = 0)
        : fileId(id), totalWords(total) {}
};

#endif
