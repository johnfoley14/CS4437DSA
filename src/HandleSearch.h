#ifndef HANDLESEACRH_H
#define HANDLESEARCH_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstring>
#include "BookInfo.h"
#include "LinkedList.h"
#include "RelevanceFunction.h"
#include "MinHeap.h"
#include "DynamicArray.h"
#include "StopWords.h"

int *parsePositions(const string &posStr, int count);
BookInfo *processCSVFiles(const string *words, int length, int fileCount, DynamicArray<string> &stopwords);
void handleSearch(string choice, DynamicArray<string> &stopwords);

#endif