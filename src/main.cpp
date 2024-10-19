#include <cstdlib>
#include <string>

#include "IndexBooks.h"
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

void clearScreen() {
#ifdef _WIN32
  std::system("cls");  // For Windows
#else
  std::system("clear");  // For Linux and macOS
#endif
}

int main() {
  string choice;
  bool quit = false;
  clearScreen();

  while (!quit) {
    printChoices();
    getline(cin, choice);
    clearScreen();

    switch (choice[0]) {
      case '1':
        cout << "You selected: 1 - Reload indexed books" << endl;
        indexAllBooks();
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
    cout << endl;
  }
  return 0;
}