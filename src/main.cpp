#include <string>

#include "Parse.h"
#include "ProcessInput.h"
#include "IndexBooks.h"

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
        createCSVs();
        break;
      case '2':
        sanitizeLine(choice).display();
        break;
      case '3':
        cout << "You selected 3" << endl;
        break;
      case '4':
        cout << "Quitting program..." << endl;
        quit = true;
        continue;
      default:
        cout << "Invalid input, please structure your input as <Choice Number> "
                "<List of optional args>\r\n";
    }
    printChoices();
  }
  return 0;
}