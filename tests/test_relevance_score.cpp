#include <gtest/gtest.h>
#include "BookInfo.h"
#include "HandleSearch.h"
#include "RelevanceFunction.h"
#include "DynamicArray.h"

string words[] = {"test_dummy_data", "test_dummy_data2"};
int length = 2;     // Number of words searched for
int fileCount = 10; // this should be the max number of files we have (ie biggest file ID)
// Call the function to process CSV files and get the array of BookInfo
DynamicArray<string> stopwords = getStopWords();
BookInfo *bookInfos = processCSVFiles(words, length, fileCount, stopwords);

// Test case to make sure the BookInfo array is not null
TEST(ProcessCSVFilesTest, BookInfosNotNull)
{
    ASSERT_NE(processCSVFiles(words, length, fileCount, stopwords), nullptr);
}

// Test case to check if the bookInfos array is allocated correctly
TEST(ProcessCSVFilesTest, BookInfosAllocation)
{
    // expect fileID to be the index of the bookInfo

    // if there is no data for a file for a certain word, there should be a nullptr for the words list for that file
    ASSERT_EQ(bookInfos[6].words.head, nullptr);
    ASSERT_EQ(bookInfos[8].words.head, nullptr);

    // make sure the file info assigns the total word count correctly
    ASSERT_EQ(bookInfos[3].totalWords, 200);
    ASSERT_EQ(bookInfos[2].totalWords, 150);

    // make sure linked list of word info is created correctly for files that have the searched strings
    // check the first word for the file info corresponds to "test dummy data 2" index file and has its positions correct
    int test_dummy_data2_positions_fileID_1[] = {1, 2, 3, 504};
    for (int i = 0; i < 4; ++i)
    {
        ASSERT_EQ(bookInfos[1].words.get(1).positions[i], test_dummy_data2_positions_fileID_1[i]);
    }
    // check the second word for the file info corresponds to "test dummy data" index file and has its positions correct
    ASSERT_EQ(bookInfos[1].words.get(0).positions[0], 4);

    // check the count for both words for a fileID = 1 is correct
    ASSERT_EQ(bookInfos[1].words.get(0).count, 2);
    ASSERT_EQ(bookInfos[1].words.get(1).count, 4);
}
