#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstring>
#include "FileInfo.h"
#include "LinkedList.h"
#include "LinkedList.cpp"

using namespace std;

// Helper function to parse a string like "[1, 2, 3]" into an array of integers
int *parsePositions(const string &posStr, int count)
{
    int *positions = new int[count];
    stringstream ss(posStr.substr(1, posStr.size() - 2)); // Remove square brackets
    string token;
    int index = 0;

    while (getline(ss, token, ',') && index < count)
    {
        positions[index++] = stoi(token);
    }

    return positions;
}

// Main function that allocates FileInfo array and updates the fileInfo with CSV data
FileInfo *processCSVFiles(const string *words, int length, int fileCount)
{
    // allocate array of FileInfo, where the array size is the max number of files we have
    // the fileID will be used as the index in the array
    FileInfo *fileInfos = new FileInfo[fileCount];

    // loop through the list of words searched for
    for (int i = 0; i < length; ++i)
    {
        string filename = "../index/" + words[i] + ".csv";
        ifstream file(filename);

        if (!file.is_open())
        {
            cerr << "Could not open file: " << filename << endl;
            continue;
        }

        string line;
        while (getline(file, line))
        {
            if (line.empty() || line == ",,,")
            {
                continue; // Skip empty lines or lines with just commas
            }

            stringstream ss(line);
            string fileIdStr, positionsStr, countStr, totalWordsStr;

            // extract file data, separated by commas
            getline(ss, fileIdStr, ',');
            getline(ss, positionsStr, ',');

            // If fileIdStr is empty, it means this is a line like ",,,", so we skip it
            if (fileIdStr.empty())
            {
                continue;
            }

            // Check if positionsStr is valid
            if (positionsStr.empty())
            {
                cerr << "Error: positionsStr is empty in file: " << filename << endl;
                continue;
            }

            // Check if positionsStr starts with a quote and extract correctly
            if (positionsStr[0] == '"')
            {
                string temp;
                while (positionsStr.back() != '"')
                {
                    getline(ss, temp, ',');
                    positionsStr += "," + temp; // Concatenate until closing quote is found
                }
            }

            // Check that positionsStr has valid content
            if (positionsStr.size() <= 2) // Minimal valid string would be "[]"
            {
                cerr << "Error: invalid positionsStr format in file: " << filename << endl;
                continue;
            }

            // Remove the quotes around positionsStr
            positionsStr = positionsStr.substr(1, positionsStr.size() - 2);

            getline(ss, countStr, ',');
            getline(ss, totalWordsStr, ',');

            // Check if any required field is empty, and skip the line if so
            if (fileIdStr.empty() || countStr.empty() || totalWordsStr.empty() || positionsStr.empty())
            {
                cerr << "Error: Invalid line in file: " << filename << endl;
                continue; // Skip invalid lines
            }

            int fileId = stoi(fileIdStr);
            int count = stoi(countStr);
            int totalWords = stoi(totalWordsStr);

            // Parse the positions string into an array of integers
            int *positions = parsePositions(positionsStr, count);

            if (fileId >= 0 && fileId < fileCount)
            {
                fileInfos[fileId].fileId = fileId;
                fileInfos[fileId].totalWords = totalWords;

                WordInfo wordInfo(count, 0.0f, positions); // Assuming score is 0.0, NOTE to talk with team about this to have precalculated score in CSV and parsed also
                fileInfos[fileId].words.append(wordInfo);
            }

            delete[] positions;
        }

        file.close(); // Close the file after reading
    }
    return fileInfos;
}

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

    delete[] fileInfos;
    return 0;
}
