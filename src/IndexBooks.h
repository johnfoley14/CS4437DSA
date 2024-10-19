#ifndef INDEXBOOKS_H
#define INDEXBOOKS_H

#include <cctype>
#include <fstream>
#include <iostream>
#include <filesystem>
#include <map>
#include <sstream>
#include <string>

#include "ProcessInput.h"

namespace fs = filesystem;

pair<int, map<string, int>> countWordsInBook(string filePath);
string appendToBookMetadata(string bookName, int totalWords);
void appendToCSV(string filePath, string row);
void indexAllBooks();
void indexBook(string bookName);
void updateWordCSVs(string bookId, map<string, int> wordCount);

#endif