#include <gtest/gtest.h>
#include "FileInfo.h"
#include "Parse.h"
#include "RelevanceFunction.h"

string words[] = {"test_dummy_data", "test_dummy_data2"};
int length = 2;     // Number of words searched for
int fileCount = 10; // this should be the max number of files we have (ie biggest file ID)
// Call the function to process CSV files and get the array of FileInfo
FileInfo *fileInfos = processCSVFiles(words, length, fileCount);

// Test case to make sure the FileInfo array is not null
TEST(ProcessCSVFilesTest, FileInfosNotNull)
{
    ASSERT_NE(processCSVFiles(words, length, fileCount), nullptr);
}

// Test case to check if the fileInfos array is allocated correctly
TEST(ProcessCSVFilesTest, FileInfosAllocation)
{
    // expect fileID to be the index of the fileInfo
    ASSERT_EQ(fileInfos[1].fileId, 1);
    ASSERT_EQ(fileInfos[4].fileId, 4);
    ASSERT_EQ(fileInfos[5].fileId, 5);

    // if there is no data for a file for a certain word, there should be a nullptr for the words list for that file
    ASSERT_EQ(fileInfos[6].words.head, nullptr);
    ASSERT_EQ(fileInfos[8].words.head, nullptr);

    // make sure the file info assigns the total word count correctly
    ASSERT_EQ(fileInfos[3].totalWords, 200);
    ASSERT_EQ(fileInfos[2].totalWords, 150);

    // make sure linked list of word info is created correctly for files that have the searched strings
    // check the first word for the file info corresponds to "test dummy data 2" index file and has its positions correct
    int test_dummy_data2_positions_fileID_1[] = {1, 2, 3, 504};
    for (int i = 0; i < 4; ++i)
    {
        ASSERT_EQ(fileInfos[1].words.get(1).positions[i], test_dummy_data2_positions_fileID_1[i]);
    }
    // check the second word for the file info corresponds to "test dummy data" index file and has its positions correct
    ASSERT_EQ(fileInfos[1].words.get(0).positions[0], 4);

    // check the count for both words for a fileID = 1 is correct
    ASSERT_EQ(fileInfos[1].words.get(0).count, 2);
    ASSERT_EQ(fileInfos[1].words.get(1).count, 4);
}

// Test case to check if getSearchRelevanceScore calculates scores correctly
TEST(GetSearchRelevanceScoreTest, ScoreCalculation)
{
    // scores are based off the summation of precalculated scores on wordInfos
    // plus the bonus marks awarded for proximity of search words in a file

    // this file info data is awarded (5, 5, 4, 3) scores for promixity
    // there is no precalculated scores on this fileInfo's wordInfo objects
    // (Feel free to look at test_dummy_data CSV's to see the data)
    ASSERT_EQ(getSearchRelevanceScore(fileInfos[1]), 17.0f);
    // this file info data is awarded (5, 4, 1, 5, 5, 2, 5, 4, 3) scores for promixity
    ASSERT_EQ(getSearchRelevanceScore(fileInfos[2]), 34.0f);
}
