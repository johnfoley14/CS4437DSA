#include "RelevanceFunction.h"

using namespace std;

// gets the score of a word in a file. This is a precalculated score that is stored in the CSV index file
float getWordRelevanceScore(int wordCount, int totalWords, int filesContainingWord)
{
    float relevanceInFile = (float)wordCount / totalWords;
    float inverseIndexScore = relevanceInFile / filesContainingWord;
    return inverseIndexScore * 1000; // multiply by 1000 to scale
}

// NOTE these values may need to be tweaked depending on how big relevance scores we are getting once we have files loaded in
float calculateBonusMarks(int pos1, int pos2)
{
    int distance = abs(pos1 - pos2);

    if (distance == 1)
        return 1.0;
    else if (distance == 2)
        return 0.5;
    else if (distance == 3)
        return 0.25;
    else if (distance == 4)
        return 0.125;
    else if (distance == 5)
        return 0.0625;

    return 0.0;
}

// take in a single file and return the bookInfo score for multiple words searched
float getSearchRelevanceScore(BookInfo bookInfos)
{
    float totalScore = 0.0f;
    int totalBonusMarks = 0;

    // Retrieve the list of WordInfo from bookInfos
    LinkedList<WordInfo> &words = bookInfos.words;

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

            if (word2Node->data.score < 0)
            {
                cout << "Negative score found" << bookInfos.fileId << endl;
                word2Node = word2Node->next;
                continue;
            }
            WordInfo &word2 = word2Node->data;
            int endIndex = 0;
            // Compare positions in word1 with positions in word2
            for (int i = 0; i < word1.count; ++i)
            {
                // start at the endIndex which is where the last comparison left off minus 10 (5 positions either side)
                // this is an optimization to avoid comparing a big number in word.positions with the small numbers in word2.positions
                // instead start from the minimum position that could be close
                for (int j = endIndex; j < word2.count; ++j)
                {
                    // exit early if the second files items are 5 greater than the first
                    // we know that after this all the other positions will be greater
                    if ((word2.positions[j] - word1.positions[i]) > 5)
                    {
                        endIndex = (j - 10) > 0 ? j - 10 : 0;
                        j = word2.count;
                    }
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
