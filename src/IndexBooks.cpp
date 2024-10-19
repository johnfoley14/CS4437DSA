#include "IndexBooks.h"

string toLowerCase(const string &str) {
  string result;
  for (char ch : str) {
    result += tolower(ch);
  }
  return result;
}

void removePunctuationUpdateMap(const string &str, map<string, int> &wordCount) {
    string result;

    for (size_t i = 0; i < str.length(); ++i) {
        char ch = str[i];

        // alpha num chars and apostrophes eg. "it's" -> "its"
        if (isalnum(ch) || ch == '\'') {
            result += ch;
        }
        // hyphens eg. "high-powered rocketry", as 3 different words
        else if (ch == '-') {
            if (!result.empty()) {
                wordCount[toLowerCase(result)]++;  // incrementing or adding for the first time
                result = "";
            }
        }
        // end of word ".", "!", "?", ",", ";" etc
        else {
            if (!result.empty()) {
                wordCount[toLowerCase(result)]++;  
                result = "";  
            }
        }
    }

    // adding word after last alpha char
    if (!result.empty()) {
        wordCount[toLowerCase(result)]++;
    }
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
      removePunctuationUpdateMap(toLowerCase(word), wordCount);

    
    }
  }

  // Close the file
  file.close();

  // Output the word frequency
  std::cout << "Word Frequencies:" << std::endl;
  // For testing purposes - DELETE ME
  ofstream out("../count_book.txt");
  if (!out.is_open()) {
      cerr << "Failed to open output file." << endl;
      return;
  }
  for (const auto &entry : wordCount) {
      out << entry.first << ": " << entry.second << endl;
      std::cout << entry.first << ": " << entry.second << std::endl;
  }
  out.close();
}