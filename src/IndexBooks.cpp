#include "IndexBooks.h"

void createCSVs() {
  ifstream file("../books/A Room with a View_2641.txt");
  if (!file.is_open()) {
    cerr << "Error: Could not open the file!" << endl;
    return;
  }

  map<string, int> wordCount;
  string line, word;

  // Read each line of the file
  while (std::getline(file, line)) {
    LinkedList<string> words = sanitizeLine(line);

    // Read each word from the line
    for (string word : words) {
      wordCount[word]++;
    }
  }

  // Close the file
  file.close();

  // Output the word frequency
  cout << "Word Frequencies:" << endl;
  for (const auto &entry : wordCount) {
    cout << entry.first << ": " << entry.second << endl;
  }
}