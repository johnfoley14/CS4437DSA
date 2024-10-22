#include "IndexBooks.h"

void countWordsInBook(string filePath, WordsInBook& result) {
  ifstream file(filePath);
  if (!file.is_open()) {
    cerr << "Error: Could not open the file!" << endl;
    return;
  }

  HashMap<string, WordMetadata*>* wordCounts = new HashMap<string, WordMetadata*>();
  string line, word;
  int totalCount = 0;
  int position = 0;

  // Maxing to 10 words for testing
  while (getline(file, line)) {
    LinkedList<string> words = sanitizeLine(line);

    // Read each word from the line
    for (const string& word : words) {
      WordMetadata* wordMeta = new WordMetadata();
      if (wordCounts->get(word, wordMeta)) {
        wordMeta->count++;
        wordMeta->positions.append(position);
        wordCounts->insert(word, wordMeta);  // updating existing
      } else {
        wordMeta->count = 1;
        wordMeta->positions.append(position);
        wordCounts->insert(word, wordMeta);  // inserting new
      }
      totalCount++;
      position++;
    }
  }
  WordMetadata* myWordMeta = new WordMetadata();

  file.close();
  WordsInBook* newResult = new WordsInBook{totalCount, *wordCounts};
  result = *newResult;
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
  linePos -= 2;
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

void updateWordCSVs(string bookId, WordsInBook& words) {
  LinkedList<pair<string, WordMetadata*>> entries =
      words.data.getAll();  // change me to LinkedList
  for (const auto& entry : entries) {
    string filePath = "../index/words/" + entry.first + ".csv";

    if (bookId != "1") {
      addPreviousRows(filePath, bookId);
    }

    string row = bookId + ',' + to_string(entry.second->count);
    row += ",\"[";
    int i = 0;
    // TODO add 'exists' method to LinkedList
    while (entry.second->positions.exists(i)) {
      row += to_string(entry.second->positions.get(i)) + ',';
      i++;
    }
    row.pop_back();
    row += "]\"";
    appendToCSV(filePath, row);
  }

  // Add book to word CSVs that the book didn't contain that word
  string emptyRow = bookId + ',';
  for (const auto& entry : fs::directory_iterator("../index/words/")) {
    if (fs::is_regular_file(entry.status())) {
      string word = entry.path().stem().string();
      WordMetadata* dummyValue;
      // need to check if the word is already in the book with dummyValue
      if (!words.data.get(word, dummyValue)) {
        appendToCSV(entry.path().string(), emptyRow);
      }
    }
  }
}

int countBooksWithWord(string filePath) {
  int result = 0;
  ifstream file(filePath);

  if (!file.is_open()) {
    cerr << "Error: Could not open the file:" << filePath << endl;
    return 0;
  }

  string currentLine;

  while (getline(file, currentLine)) {
    stringstream ss(currentLine);
    string currentWordCount;
    string discard;

    getline(ss, discard, ',');
    getline(ss, currentWordCount, ',');

    if (currentWordCount != "") {
      result++;
    }
  }
  return result;
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

void updateWordMetadata() {
  if (fs::exists("../index/WordMetadata.csv")) {
    fs::remove("../index/WordMetadata.csv");
  }

  for (const auto& entry : fs::directory_iterator("../index/words/")) {
    if (fs::is_regular_file(entry.status())) {
      int booksContainingWord = countBooksWithWord(entry.path().string());
      string row =
          entry.path().stem().string() + ',' + to_string(booksContainingWord);

      appendToCSV("../index/WordsMetadata.csv", row);
    }
  }
}

void addRelevanceScores() {
  for (const auto& entry : fs::directory_iterator("../index/words/")) {
    if (fs::is_regular_file(entry.status())) {
      int booksContainingWord = countBooksWithWord(entry.path().string());
      string scoreFilePath =
          "../index/scores/" + entry.path().stem().string() + ".csv";
      string row;

      if (fs::exists(scoreFilePath)) {
        fs::remove(scoreFilePath);
      }

      ifstream wordFile(entry.path());
      ifstream bookFile("../index/BookMetadata.csv");

      string currentBook;
      string totalInBook;
      string currentLine;
      string discard;
      string countInBook;
      while (getline(wordFile, currentLine)) {
        getline(bookFile, currentBook);
        stringstream ssBook(currentBook);
        stringstream ssWord(currentLine);

        getline(ssWord, discard, ',');  // Discard bookId
        getline(ssWord, countInBook);

        getline(ssBook, discard, ',');
        getline(ssBook, discard, ',');
        getline(ssBook, totalInBook);

        if (countInBook != "") {
          int count = stoi(countInBook);
          int countInBook = stoi(totalInBook);
          float relevance =
              getWordRelevanceScore(count, countInBook, booksContainingWord);
          row = to_string(relevance);
        } else {
          row = "";
        }

        appendToCSV("../index/scores/" + entry.path().stem().string() + ".csv",
                    row);
      }
    }
  }
}

// Create the required directories if they don't exist
void createIndexDirs() {
  const vector<string> requiredPaths = {"../index/words/", "../index/scores/"};

  for (string path : requiredPaths) {
    if (!fs::exists(path)) {
      if (fs::create_directories(path)) {
        cout << "Created required directories: " << path << endl;
      } else {
        cerr << "Failed to create required directories!" << endl;
      }
    }
  }
}

void indexBook(string bookName) {
  if (bookIsIndexed(bookName)) {
    return;
  }

  cout << "Attempting to indexed new book: " << bookName << endl;

  string path = "../books/" + bookName + ".txt";

  WordsInBook* words = new WordsInBook;
  countWordsInBook(path, *words);

  cout << "Finished reading in book: " << bookName << endl;

  string bookId = appendToBookMetadata(bookName, words->totalWords);
  updateWordCSVs(bookId, *words);

  cout << "Successfully indexed new book: " << bookName << endl;
  delete words;
}

void indexAllBooks() {
  auto start = chrono::high_resolution_clock::now();
  createIndexDirs();
  if (!fs::exists("../books/")) {
    cerr << "No books directory found!" << endl;
    return;
  }

  int totalBooks = 0;
  for (const auto& entry : fs::directory_iterator("../books/")) {
    if (fs::is_regular_file(entry.status())) {
      indexBook(entry.path().stem().string());
      totalBooks++;
    }
  }

  if (fs::exists("../index/Overview.csv")) {
    fs::remove("../index/Overview.csv");
  }

  string row = "totalBooks," + to_string(totalBooks);
  appendToCSV("../index/Overview.csv", row);
  updateWordMetadata();
  addRelevanceScores();
  auto end = chrono::high_resolution_clock::now();
  auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);

  cout << "Indexing all books took " << duration.count() << " milliseconds."
       << endl;
}