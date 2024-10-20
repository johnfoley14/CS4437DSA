#ifndef INDEXBOOKS_H
#define INDEXBOOKS_H

#include <cctype>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>

#include "ProcessInput.h"
#include "RelevanceFunction.h"

namespace fs = filesystem;

struct WordMetadata {
    int count;
    std::vector<int> positions;
};

struct WordsInBook {
  int totalWords;
  map<string, WordMetadata> data;
};

WordsInBook countWordsInBook(string filePath);
string appendToBookMetadata(string bookName, int totalWords);
void appendToCSV(string filePath, string row);
void indexAllBooks();
void indexBook(string bookName);
void updateWordCSVs(string bookId, map<string, int> wordCount);
int countBooksWithWord(string filePath);
void updateWordMetadata();

#endif