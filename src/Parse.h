#ifndef PARSE_H
#define PARSE_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstring>
#include "BookInfo.h"
#include "LinkedList.h"
#include "RelevanceFunction.h"

int *parsePositions(const string &posStr, int count);
BookInfo *processCSVFiles(const string *words, int length, int fileCount);

#endif