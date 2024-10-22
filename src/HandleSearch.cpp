#include "HandleSearch.h"
#include <chrono>

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

// Main function that allocates BookInfo array and updates the BookInfo with CSV data
BookInfo *processCSVFiles(const string *words, int length, int fileCount, DynamicArray<string> &stopwords)
{
    // allocate array of BookInfo, where the array size is the max number of files we have
    // the fileID will be used as the index in the array
    BookInfo *bookInfos = new BookInfo[fileCount + 1];
    bool notFlag = false;

    // loop through the list of words searched for
    for (int i = 0; i < length; ++i)
    {
        if (words[i] == "NOT")
        {
            notFlag = true;
            continue;
        }
        if (isStopWord(words[i], stopwords))
        {
            continue;
        }

        string filename = "../index/words/" + words[i] + ".csv";
        ifstream file(filename);
        ifstream scoreFile("../index/scores/" + words[i] + ".csv");
        ifstream bookMetadata("../index/BookMetadata.csv");

        if (!file.is_open() || !scoreFile.is_open() || !bookMetadata.is_open())
        {
            cerr << "Could not open file: " << words[i] << endl;
            continue;
        }

        string line, scoresLine, bookLine;
        while (getline(file, line) && getline(scoreFile, scoresLine) && getline(bookMetadata, bookLine))
        {
            if (line.empty() || line == ",,,")
            {
                continue; // Skip empty lines or lines with just commas
            }

            stringstream ss(line);
            string fileIdStr, positionsStr, countStr, totalWordsStr;

            // extract file data, separated by commas
            getline(ss, fileIdStr, ',');
            getline(ss, countStr, ',');
            getline(ss, positionsStr, ',');

            // If fileIdStr is empty, it means this is a line like ",,,", so we skip it
            if (countStr.empty())
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

            // Check if any required field is empty, and skip the line if so
            if (fileIdStr.empty() || countStr.empty() || positionsStr.empty())
            {
                cerr << "Error: Invalid line in file: " << filename << endl;
                continue; // Skip invalid lines
            }
            int fileId = stoi(fileIdStr);
            int count = stoi(countStr);
            float score = stof(scoresLine); // Default score value for now, to be calculated later in the project

            stringstream metadataS(bookLine);
            string temp2;
            // First column (ID)
            getline(metadataS, temp2, ',');

            // Second column (Title with underscore and ID)
            getline(metadataS, temp2, ',');

            // Find the position of the underscore
            size_t underscore_pos = temp2.find('_');

            // Extract the title before the underscore
            string title = temp2.substr(0, underscore_pos);

            // if notFlag, it means we had NOT before this word in the search, so we want to negate the score so files with more of this word are ranked lower
            if (notFlag)
            {
                score = -score;
            }

            // Parse the positions string into an array of integers
            int *positions = parsePositions(positionsStr, count);

            if (fileId >= 0 && fileId < fileCount)
            {
                bookInfos[fileId].fileId = fileId;
                bookInfos[fileId].title = title;

                WordInfo wordInfo(count, score, positions);
                bookInfos[fileId].words.append(wordInfo);
            }

            delete[] positions;
        }

        file.close(); // Close the file after reading
        notFlag = false;
    }
    return bookInfos;
}

int countWords(const string &input)
{
    istringstream iss(input);
    string word;
    int wordCount = 0;

    // Count words by reading from the input stream
    while (iss >> word)
    {
        wordCount++;
    }

    // Subtract 1 to exclude the first word which is the number representing the option picked (2 in this case)
    return (wordCount > 0) ? wordCount - 1 : 0;
}

void splitStringIntoArray(const string &input, string *output, int wordCount)
{
    istringstream iss(input);
    string word;
    int index = 0;

    // Skip the first word which is the option number
    iss >> word;

    // Split the string by spaces and insert the remaining words into the array
    while (iss >> word && index < wordCount)
    {
        output[index++] = word;
    }
}

void printResults(MinHeap &resultsHeap)
{
    string output = "";
    int startRankNum = resultsHeap.heapSize;
    while (resultsHeap.heapSize > 0)
    {
        BookScore book = resultsHeap.extractMin();
        output += to_string(startRankNum) + ". " + book.title + " Search Score: " + to_string(book.score) + "\n";
        startRankNum--;
    }
    cout << output;
    return;
}

void handleSearch(string choice, DynamicArray<string> &stopwords)
{
    int wordCount = countWords(choice);

    string *output = new string[wordCount];
    // split the searched string into an array of words
    splitStringIntoArray(choice, output, wordCount);

    ifstream file("../index/Overview.csv");
    if (!file.is_open())
    {
        cerr << "Could not open Overview.csv " << endl;
        return;
    }

    string line;
    int totalBooks = 0;

    while (getline(file, line))
    {
        if (line.empty())
        {
            continue; // Skip empty lines
        }

        stringstream ss(line);
        string key, value;

        getline(ss, key, ',');
        getline(ss, value, ',');

        totalBooks = stoi(value);
    }
    BookInfo *searchBookInfos = processCSVFiles(output, wordCount, totalBooks, stopwords);
    MinHeap heap(50);
    auto start = chrono::high_resolution_clock::now();

    for (int i = 0; i < totalBooks; i++)
    {
        // if the book has no occurences of the searched words, we skip it
        if (searchBookInfos[i].words.head == nullptr)
        {
            continue;
        }

        // for the first 50 books, we insert them into the heap as BookScore {fileId, score}
        if (heap.heapSize < 50)
        {
            heap.insert({searchBookInfos[i].fileId, getSearchRelevanceScore(searchBookInfos[i]), searchBookInfos[i].title});
        }
        else
        {
            if (getSearchRelevanceScore(searchBookInfos[i]) > heap.getMin().score)
            {
                heap.extractMin();
                heap.insert({searchBookInfos[i].fileId, getSearchRelevanceScore(searchBookInfos[i]), searchBookInfos[i].title});
            }
        }
    }

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = end - start;
    cout << "Time taken by loop: " << elapsed.count() << " seconds" << endl;
    printResults(heap);
    return;
}
