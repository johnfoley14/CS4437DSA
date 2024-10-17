#include "RelevanceFunction.h"

using namespace std;

// gets the score of a word in a file. This is a precalculated score that is stored in the CSV index file
static float getWordRelevanceScore(int wordCount, int totalWords, int filesContainingWord)
{
    float relevanceInFile = (float)wordCount / totalWords;
    float inverseIndexScore = relevanceInFile / filesContainingWord;
    return inverseIndexScore;
}

// NOTE these values may need to be tweaked depending on how big relevance scores we are getting once we have files loaded in
int calculateBonusMarks(int pos1, int pos2)
{
    int distance = abs(pos1 - pos2);

    if (distance == 1)
        return 5;
    else if (distance == 2)
        return 4;
    else if (distance == 3)
        return 3;
    else if (distance == 4)
        return 2;
    else if (distance == 5)
        return 1;

    return 0;
}

// why is the ability to index a CSV file important?

// take in a single file and return the fileInfo score for multiple words searched
float getSearchRelevanceScore(FileInfo fileInfos)
{
    float totalScore = 0.0f;
    int totalBonusMarks = 0;

    // Retrieve the list of WordInfo from fileInfos
    LinkedList<WordInfo> &words = fileInfos.words;

    Node<WordInfo> *word1Node = words.head;

    // Loop through each WordInfo for a file
    while (word1Node != nullptr)
    {
        WordInfo &word1 = word1Node->data;

        // Add the precalculated score of the current WordInfo to the total score
        totalScore += word1.score;

        Node<WordInfo> *word2Node = word1Node->next;

        // Compare this word1 with all words after it and calculate bonus marks if words are close
        while (word2Node != nullptr)
        {
            WordInfo &word2 = word2Node->data;

            // Compare positions in word1 with positions in word2
            for (int i = 0; i < word1.count; ++i)
            {
                for (int j = 0; j < word2.count; ++j)
                {
                    int pos1 = word1.positions[i];
                    int pos2 = word2.positions[j];

                    // Calculate bonus marks based on proximity
                    int bonus = calculateBonusMarks(pos1, pos2);
                    totalBonusMarks += bonus;
                }
            }

            word2Node = word2Node->next; // Move to the next WordInfo for comparison
        }

        word1Node = word1Node->next; // Move to the next WordInfo
    }

    // Return the combined score and bonus marks
    return totalScore + (float)totalBonusMarks;
}
