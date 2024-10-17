#ifndef PARSE_H
#define PARSE_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstring>
#include "FileInfo.h"
#include "LinkedList.h"
#include "RelevanceFunction.h"

int *parsePositions(const string &posStr, int count);
FileInfo *processCSVFiles(const string *words, int length, int fileCount);

#endif