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

int *parsePositions(const string &posStr, int count);
BookInfo *processCSVFiles(const string *words, int length, int fileCount);
void handleSearch(string choice);

#endif