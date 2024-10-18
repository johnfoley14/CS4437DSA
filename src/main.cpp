#include <string>

#include "Parse.h"
#include "ProcessInput.h"

void printChoices() {
  cout << "Your choices are:\n\r"
          "1 - Reload indexed books\n\r"
          "2 <keywords> - Search for a book using a list of keywords\n\r"
          "3 <word> - Autocomplete\n\r"
          "4 - Quit\n\r"
          "Please enter your choice:"
       << endl;
}

int main() {
  string choice;
  bool quit = false;

  printChoices();

  while (!quit) {
    getline(cin, choice);

    switch (choice[0]) {
      case '1':
        cout << "You selected 1" << endl;
        break;
      case '2':
        getKeywords(choice).display();
        printChoices();
        break;
      case '3':
        cout << "You selected 3" << endl;
        break;
      case '4':
        cout << "You selected 4" << endl;
        break;
      default:
        cout << "Invalid input, please structure your input as <Choice Number> "
                "<List of optional args>";
    }
  }
  return 0;
}