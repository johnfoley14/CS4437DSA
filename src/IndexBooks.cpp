#include "IndexBooks.h"

string toLowerCase(const string &str) {
  string result;
  for (char ch : str) {
    result += tolower(ch);
  }
  return result;
}

string removePunctuation(const string &str) {
  string result;
  for (char ch : str) {
    if (isalnum(ch) || ch == '\'') {
      result += ch;
    }
  }
  return result;
}

void createCSVs() {
  ifstream file("../books/A Room with a View_2641.txt");
  if (!file.is_open()) {
    std::cerr << "Error: Could not open the file!" << std::endl;
    return;
  }

  map<string, int> wordCount;
  string line, word;

  // Read each line of the file
  while (std::getline(file, line)) {
    std::stringstream ss(line);

    // Read each word from the line
    while (ss >> word) {
      // Clean up the word by converting to lowercase and removing punctuation
      word = removePunctuation(toLowerCase(word));

      // Skip empty words (if any)
      if (!word.empty()) {
        ++wordCount[word];  // Increment word count
      }
    }
  }

  // Close the file
  file.close();

  // Output the word frequency
  std::cout << "Word Frequencies:" << std::endl;
  for (const auto &entry : wordCount) {
    std::cout << entry.first << ": " << entry.second << std::endl;
  }
}