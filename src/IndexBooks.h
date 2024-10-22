#ifndef INDEXBOOKS_H
#define INDEXBOOKS_H

#include <cctype>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

#include "ProcessInput.h"
#include "RelevanceFunction.h"
#include "DynamicArray.h"
#include "HashMap.h"

namespace fs = filesystem;

struct WordMetadata
{
  int count;
  LinkedList<int> positions;
};

struct WordsInBook
{
  int totalWords;
  HashMap<string, WordMetadata*> data;
};

void countWordsInBook(string filePath, WordsInBook&  result);
string appendToBookMetadata(string bookName, int totalWords);
void appendToCSV(string filePath, string row);
void indexAllBooks();
void indexBook(string bookName);
void updateWordCSVs(string bookId, WordsInBook& words);
int countBooksWithWord(string filePath);
void updateWordMetadata();

#endif