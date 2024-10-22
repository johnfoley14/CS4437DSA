#ifndef RELEVANCEFUNCTION_H
#define RELEVANCEFUNCTION_H

#include <cmath> // For abs()
#include "BookInfo.h"
#include "LinkedList.h"

// Gets the word relevance score based on word count, total words in the file, and the number of files containing the word
float getWordRelevanceScore(int wordCount, int totalWords, int filesContainingWord);

// Calculates bonus marks based on the proximity of word positions in the file
float calculateBonusMarks(int pos1, int pos2);

// Returns the search relevance score for the file based on multiple words searched and their positions
float getSearchRelevanceScore(BookInfo bookInfos);

#endif
