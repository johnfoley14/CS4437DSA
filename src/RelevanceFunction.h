#ifndef RELEVANCEFUNCTION_H
#define RELEVANCEFUNCTION_H

#include <vector>
#include <cmath> // For abs()
#include "FileInfo.h"
#include "LinkedList.h"

// Gets the word relevance score based on word count, total words in the file, and the number of files containing the word
static float getWordRelevanceScore(int wordCount, int totalWords, int filesContainingWord);

// Calculates bonus marks based on the proximity of word positions in the file
int calculateBonusMarks(int pos1, int pos2);

// Returns the search relevance score for the file based on multiple words searched and their positions
float getSearchRelevanceScore(FileInfo fileInfos);

#endif
