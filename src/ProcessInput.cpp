#include "ProcessInput.h"

LinkedList<string> getKeywords(string argString) {
  LinkedList<string> output;
  string currentWord = "";
  bool completeWord = false;

  for (int i = 1; i < argString.length(); i++) {
    while (argString[i] != ' ' && i < argString.length()) {
      if (isalnum(argString[i])) {
        currentWord += argString[i];
      }
      i++;
    }
    output.append(currentWord);
    currentWord = "";
  }

  return output;
}