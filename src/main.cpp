#include "Parse.h"

int main()
{
    // example usage to read data and store in FileInfo array where file info can be used to calulate max scores.

    string words[] = {"animal", "dog"};
    int length = 2;     // Number of words searched for
    int fileCount = 10; // this should be the max number of files we have (ie biggest file ID)

    // Call the function to process CSV files and get the array of FileInfo
    FileInfo *fileInfos = processCSVFiles(words, length, fileCount);

    for (int i = 0; i < fileCount; ++i)
    {
        if (fileInfos[i].fileId != 0 || fileInfos[i].totalWords != 0)
        {
            cout << "File ID: " << fileInfos[i].fileId << "\n";
            cout << "Total Words: " << fileInfos[i].totalWords << "\n";
            cout << "WordInfo entries: \n";
            fileInfos[i].words.display();
        }
    }

    float score = getSearchRelevanceScore(fileInfos[1]);
    cout << "Score for file 1: " << score << endl;

    float score2 = getSearchRelevanceScore(fileInfos[2]);
    cout << "Score for file 2: " << score2 << endl;
    delete[] fileInfos;
    return 0;
}