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

  // Maxing to 10 words for testing
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

string getLastLine(string filePath) {
  ifstream file(filePath);

  if (!file.is_open()) {
    cerr << "Error opening file: " << filePath << endl;
    return "";
  }

  file.seekg(0, ios::end);

  streampos linePos = file.tellg();
  linePos -= 1;
  char ch;

  while (linePos > 0) {
    linePos -= 1;
    file.seekg(linePos);
    file.get(ch);

    if (ch == '\n') {
      linePos += 1;
      break;
    }
  }

  file.seekg(linePos);
  string line;
  getline(file, line);
  return line;
}

void addPreviousRows(string filePath, string bookId) {
  int lastId = 0;
  
  if (fs::exists(filePath)) {
    string lastLine = getLastLine(filePath);
    stringstream ss(lastLine);
    string lastIdStr;
    getline(ss, lastIdStr, ',');
    lastId = stoi(lastIdStr);
  }

  for (int i = lastId + 1; i < stoi(bookId); i++) {
    string emptyRow = to_string(i) + ',';
    appendToCSV(filePath, emptyRow);
  }
}

void updateWordCSVs(string bookId, map<string, int> wordCount) {
  for (const auto& entry : wordCount) {
    string filePath = "../index/words/" + entry.first + ".csv";
    
    if (bookId != "1") {
      addPreviousRows(filePath, bookId);
    }

    string row = bookId + "," + to_string(entry.second);
    appendToCSV(filePath, row);
  }

  string emptyRow = bookId + ',';
  for (const auto& entry : fs::directory_iterator("../index/words/")) {
    if (fs::is_regular_file(entry.status())) {
      if (wordCount.find(entry.path().stem().string()) == wordCount.end()) {
        appendToCSV(entry.path(), emptyRow);
      }
    }
  }
}

bool bookIsIndexed(string bookName) {
  const string filePath = "../index/BookMetadata.csv";

  if (!fs::exists(filePath)) {
    return false;
  }

  ifstream ifile(filePath);

  if (!ifile.is_open()) {
    cerr << "Failed to open 'BookMetadata.csv' for reading!" << endl;
    return "";
  }

  string line;
  string currentBookName;
  string discard;

  while (getline(ifile, line)) {
    stringstream ss(line);

    getline(ss, discard, ',');
    getline(ss, currentBookName, ',');

    if (currentBookName == bookName) {
      ifile.close();
      return true;
    }
  }

  ifile.close();
  return false;
}

// Returns the id of the book being added
string appendToBookMetadata(string bookName, int totalWords) {
  const string filePath = "../index/BookMetadata.csv";

  if (fs::exists(filePath)) {
    string lastLine = getLastLine(filePath);
    stringstream ss(lastLine);
    string lastId;
    getline(ss, lastId, ',');

    string newId = to_string(stoi(lastId) + 1);
    string row = newId + ',' + bookName + ',' + to_string(totalWords);
    appendToCSV(filePath, row);

    return newId;
  } else {
    string row = "1," + bookName + ',' + to_string(totalWords);
    appendToCSV(filePath, row);
    return "1";
  }
}

// Create the required directories if they don't exist
void createIndexDirs() {
  const string requiredPath = "../index/words/";
  if (!fs::exists(requiredPath)) {
    if (fs::create_directories(requiredPath)) {
      cout << "Created required directories!" << endl;
    } else {
      cerr << "Failed to create required directories!" << endl;
    }
  }
}

void indexBook(string bookName) {
  if (bookIsIndexed(bookName)) {
    return;
  }

  string path = "../books/" + bookName + ".txt";

  int totalWords;
  map<string, int> wordCounts;
  tie(totalWords, wordCounts) = countWordsInBook(path);

  string bookId = appendToBookMetadata(bookName, totalWords);
  updateWordCSVs(bookId, wordCounts);

  cout << "Successfully indexed new book: " << bookName << endl;
}

void indexAllBooks() {
  createIndexDirs();
  if (!fs::exists("../books/")) {
    cerr << "No books directory found!" << endl;
    return;
  }

  for (const auto& entry : fs::directory_iterator("../books/")) {
    if (fs::is_regular_file(entry.status())) {
      indexBook(entry.path().stem().string());
    }
  }
}