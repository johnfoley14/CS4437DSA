#include "StopWords.h"

DynamicArray<string> getStopWords()
{
    DynamicArray<string> stopWords;
    ifstream file("../index/StopWords.csv");
    if (!file.is_open())
    {
        cerr << "Could not open stopwords.txt" << endl;
        return stopWords;
    }

    string line;
    while (getline(file, line))
    {
        stopWords.add(line);
    }

    file.close();
    return stopWords;
}

bool isStopWord(const string &word, DynamicArray<string> &stopWords)
{
    if (binarySearch(stopWords, word) == -1)
    {
        return false;
    }

    return true;
}

int binarySearch(const DynamicArray<string> &arr, string target)
{
    int left = 0;
    int right = arr.getSize() - 1;

    while (left <= right)
    {
        int mid = left + (right - left) / 2;

        if (arr[mid] == target)
        {
            return mid;
        }

        if (arr[mid] < target)
        {
            left = mid + 1;
        }
        else
        {
            right = mid - 1;
        }
    }

    return -1;
}