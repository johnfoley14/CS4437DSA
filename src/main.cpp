#include <cstdlib>
#include <string>

#include "HandleSearch.h"
#include "IndexBooks.h"
#include "StopWords.h"
#include "DynamicArray.h"
#include "ProcessInput.h"
#include "trie.h"

void printChoices()
{
  cout << "Your choices are:\n\r"
          "1 - Reload indexed books\n\r"
          "2 <keywords> - Search for a book using a list of keywords\n\r"
          "3 <word> - Autocomplete\n\r"
          "4 - Delete indexed entries\n\r"
          "5 - Quit"
          "Please enter your choice:"
       << endl;
}

void clearScreen()
{
#ifdef _WIN32
  std::system("cls"); // For Windows
#else
  std::system("clear"); // For Linux and macOS
#endif
}

int main()
{
  string choice;
  TrieNode root;
  bool quit = false;
  bool trieLoaded = false;
  // clearScreen();

  DynamicArray<string> stopWords = getStopWords();

  while (!quit)
  {
    printChoices();
    getline(cin, choice);
    // clearScreen();

    switch (choice[0])
    {
    case '1':
      cout << "You selected: 1 - Reload indexed books" << endl;
      indexAllBooks();
      findFileAndAddToTrie(root);
      trieLoaded = true;
      break;
    case '2':
      // handle user seach query
      handleSearch(choice, stopWords);
      break;
    case '3':
    {
      cout << "You selected 3 - Auto complete" << endl;
      if (!trieLoaded)
      {
        findFileAndAddToTrie(root);
        trieLoaded = true;
      }
      if (choice.length() <= 2)
      {
        cout << "Please provide a word for autocomplete after '3'.\n";
        break;
      }

      string word = choice.substr(2);
      DynamicArray<std::string> suggestions = searchTrie(&root, word);

      if (suggestions.getSize() == 0)
      {
        cout << "No suggestions found for: " << word << endl;
      }
      else
      {
        cout << "Autocomplete words for '" << word << "':" << endl;
        suggestions.printElements();
      }
      break;
    }
    case '4':
      cout << "Deleting..." << endl;
      deleteBooks();
      continue;
    case '5':
      cout << "Quiting program..." << endl;
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