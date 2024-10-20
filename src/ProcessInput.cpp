#include "ProcessInput.h"

LinkedList<string> sanitizeLine(string str) {
  string delimiters = " -—";
  LinkedList<string> result;

  string currentWord = "";

  for (char ch : str) {
    if (delimiters.find(ch) != string::npos) {
      if (!currentWord.empty()) {
        result.append(currentWord);
        currentWord.clear();
      }
    } else {
      if (isalnum(ch)) {
        currentWord += tolower(ch);
      }
    }
  }

  if (!currentWord.empty()) {
    result.append(currentWord);
  }

  return result;
}