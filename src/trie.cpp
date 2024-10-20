#include "trie.h"

using namespace std;

TrieNode::TrieNode() {
    isLeaf = false;
    for (int i = 0; i < 36; i++) { // 26 letters + 10 digits
        children[i] = nullptr; // Initialise all children to nullptr
    }
}

TrieNode::~TrieNode() {
    for (int i = 0; i < 36; i++) {
        if (children[i] != nullptr) {
            delete children[i];  // Recursively delete children
        }
    }
}

bool isCSV(const string& filename){
    if(filename.substr(filename.find_last_of(".")+1) == "csv"){
        return true;
    }
    else{
        return false;
    }
}

string removeExtension(const string& filename) {
    int dotPos = filename.find_last_of(".");
    if (dotPos == -1) {
        return filename;  // No extension found
    }
    return filename.substr(0, dotPos);  // Return the name without ".csv"
}

void addWordToTrie(TrieNode* root, const string& word){

    TrieNode* curr = root;
    for (char c : word) {
        int index = getCharIndex(c);
        if (index == -1){
            continue; // skipping, char != [a-z0-9]
        }  
        
        if (curr->children[index] == nullptr) {
            TrieNode* newNode = new TrieNode();
            newNode->letter = c;
            curr->children[index] = newNode;
        }
        curr = curr->children[index];
    }
    curr->isLeaf = true;


}


TrieNode* findNode(TrieNode* root, const string& partial) { // search word in trie given partial word
    TrieNode* curr = root;
    for (char c : partial) {
        int index = getCharIndex(c);
        if (index == -1 || curr->children[index] == nullptr) {
            return nullptr;  // partial word is not in trie
        }
        curr = curr->children[index];
    }
    return curr;  // Return last char of partial word to continue search (iterate through children)
}

void findWords(TrieNode* node, const string &partial, DynamicArray<std::string> &words) {
    if(node->isLeaf){
        words.add(partial); // the partial word is a word
    }

    for (int i = 0; i < 36; i++) {
        if (node->children[i] != nullptr) {
            char nextChar;
            if (i < 26) {
                nextChar = 'a' + i;  // [a-z] = 0-25
            } else {
                nextChar = '0' + (i - 26);  // [0-9] = 26-35
            }
            findWords(node->children[i], partial + nextChar, words);
        }
    }

    
}

DynamicArray<std::string> searchTrie(TrieNode* root, const string& partial) {
    TrieNode* node = findNode(root, partial);  // Finding node of last char in partial
    DynamicArray<std::string> words;

    if (node == nullptr) {
        return words;  // no words found
    }

    // Collect all words 
    findWords(node, partial, words);

    return words;
}


void findFileAndAddToTrie(TrieNode &root){
    DIR *dr = opendir("../index/words"); // directory stream
    struct dirent *en; // pointer to file information in *dr
    if (dr) {
        while ((en = readdir(dr)) != NULL) {
            if (string(en->d_name) == "." || string(en->d_name) == "..") {
                continue;  // ignore "." and ".." directories
            }

            // Check if file is a CSV
            if (isCSV(en->d_name)) {
                cout << "CSV: " << en->d_name << endl;
                addWordToTrie(&root, removeExtension(en->d_name));  // add to trie
            }
        }
        closedir(dr);  // close the directory stream
        cout << "Successfully added all words to trie!" << endl;
   }
   else{
    cout << "Failed to open directory ../index" << endl;
   }
}

int getCharIndex(char c) {
    if (isalpha(c)) {  // letters
        return tolower(c) - 'a';  // [a-z] = 0-25
    } else if (isdigit(c)) {  // number
        return 26 + (c - '0');  // [0-9] = 26-35
    }
    return -1;
}


