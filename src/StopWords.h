#ifndef StopWords_H
#define StopWords_H

#include <iostream>
#include <fstream>
#include <string>
#include "DynamicArray.h" // Include the LinkedList template class

DynamicArray<string> getStopWords();

bool isStopWord(const string &word, DynamicArray<string> &stopWords);
int binarySearch(const DynamicArray<string> &arr, string target);

#endif