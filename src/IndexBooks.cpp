#include "IndexBooks.h"

pair<int, map<string, int>> countWordsInBook(string filePath) {
  ifstream file(filePath);
  if (!file.is_open()) {
    cerr << "Error: Could not open the file!" << endl;
    return {};
  }

  map<string, int> wordCount;
  string line, word;
  int totalCount = 0;

  while (getline(file, line)) {
    LinkedList<string> words = sanitizeLine(line);

    // Read each word from the line
    for (string word : words) {
      wordCount[word]++;
      totalCount++;
    }
  }

  file.close();
  return {totalCount, wordCount};
}

void appendToCSV(string filePath, string row) {
  ofstream file(filePath, ios::app);

  if (!file.is_open()) {
    cerr << "Failed to open or create output csv: " << filePath << endl;
    return;
  }

  file << row << endl;
  file.close();
}

void updateWordCSVs(string bookId, map<string, int> wordCount) {
  // For testing purposes
  int count = 0;
  for (const auto& entry : wordCount) {
    string filePath = "../index/words/" + entry.first + ".csv";
    string row = bookId + "," + to_string(entry.second);
    if (count < 10) {
      count++;
      appendToCSV(filePath, row);
    }
  }
}

bool bookIsIndexed(string bookName) {
  const string filePath = "../index/BookMetadata.csv";
  ifstream ifile(filePath);

  if (!ifile.is_open()) {
    cerr << "Failed to open 'BookMetadata.csv' for reading!" << endl;
    return "";
  }

  string line;
  string currentBookName;

  while (getline(ifile, line)) {
    stringstream ss(line);

    getline(ss, currentBookName, ',');

    if (currentBookName == bookName) {
      ifile.close();
      return true;
    }
  }

  ifile.close();
  return false;
}

// Returns the id of the book being added, or "-1" if the book is already added
string appendToBookMetadata(string bookName, int totalWords) {
  const string filePath = "../index/BookMetadata.csv";

  if (fs::exists(filePath)) {
    ifstream ifile(filePath);

    if (!ifile.is_open()) {
      cerr << "Failed to open 'BookMetadata.csv' for reading!" << endl;
      return "";
    }

    string line;
    string currentBookName;
    string lastId;
    bool bookExists = false;

    while (getline(ifile, line)) {
      stringstream ss(line);

      getline(ss, lastId, ',');
      getline(ss, currentBookName, ',');

      if (currentBookName == bookName) {
        ifile.close();
        return "-1";
      }
    }

    ifile.close();

    cout << "lastId: " << lastId << endl;

    string newId = to_string(stoi(lastId) + 1);
    string row = newId + ',' + bookName + ',' + to_string(totalWords);
    appendToCSV(filePath, row);

    return newId;
  } else {
    ofstream file(filePath, ios::app);

    if (!file.is_open()) {
      cerr << "Failed to open or create output csv for 'BookMetadata.csv'"
           << endl;
      return "";
    }

    string row = "1," + bookName + ',' + to_string(totalWords);
    appendToCSV(filePath, row);
    return "1";
  }
}

// Create the required directories if they don't exist
void createDirs() {
  const string requiredPath = "../index/words/";
  if (!fs::exists(requiredPath)) {
    if (fs::create_directories(requiredPath)) {
      cout << "Created required directories!" << endl;
    } else {
      cout << "Failed to create required directories!" << endl;
    }
  }
}

void indexBook(string bookName) {
  string path = "../books/" + bookName + ".txt";
  int totalWords;
  map<string, int> wordCounts;
  tie(totalWords, wordCounts) = countWordsInBook(path);

  string bookId = appendToBookMetadata(bookName, totalWords);

  cout << bookId << endl;
  if (bookId != "-1") {
    updateWordCSVs(bookId, wordCounts);
  }
}

void indexAllBooks() {
  createDirs();
  try {
    if (!fs::exists("../books/")) {
      cerr << "No books directory found!" << endl;
      return;
    }

    for (const auto& entry : fs::directory_iterator("../books/")) {
      if (fs::is_regular_file(entry.status())) {
        std::cout << entry.path().stem().string() << std::endl;
      }
    }
  } catch (const fs::filesystem_error& e) {
    std::cerr << "Filesystem error: " << e.what() << std::endl;
  } catch (const std::exception& e) {
    std::cerr << "Error: " << e.what() << std::endl;
  }
}