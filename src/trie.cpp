#include "trie.h"

using namespace std;

TrieNode::TrieNode() {
    isLeaf = false;
    for (int i = 0; i < 26; i++) {
        children[i] = nullptr; // Initialise all children to nullptr
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
    for (char c : word){
        if(curr->children[c - 'a'] == nullptr){ // words must only be between[a-z], lowercase
            TrieNode* newNode = new TrieNode();
            curr->children[c - 'a'] = newNode;
    }
    curr = curr->children[c - 'a'];
    }
    curr->isLeaf = true;


}


TrieNode* findNode(TrieNode* root, const string& partial) { // search word in trie given partial word
    TrieNode* curr = root;
    for (char c : partial) {
        if (curr->children[c - 'a'] == nullptr) {
            return nullptr;  // partial word is not in trie
        }
        curr = curr->children[c - 'a'];
    }
    return curr;  // Return last char of partial word to continue search (iterate through children)
}

void findWords(TrieNode* node, const string &partial, vector<string>& words) {
    if(node->isLeaf){
        words.push_back(partial); // the partial word is a word
    }

    for (int i = 0; i < 26; i++) {
        if (node->children[i] != nullptr){
            findWords(node->children[i], partial+ (char)('a'+i), words);
        }
    }

    
}

vector<string> searchTrie(TrieNode* root, const string& partial) {
    TrieNode* node = findNode(root, partial);  // Finding node of last char in partial
    vector<string> words;

    if (node == nullptr) {
        return words;  // no words found
    }

    // Collect all words 
    findWords(node, partial, words);

    return words;
}


void findFileAndAddToTrie(TrieNode &root){
    DIR *dr = opendir("../index"); // directory stream
    struct dirent *en; // pointer to all info about file in *dr
    if (dr) {
        while ((en = readdir(dr)) != NULL) {
            if(string(en->d_name) == "." || string(en->d_name) == ".."){ // ignoring . and .. directory
            continue;
        }
        else{
            // process all csv in index directory
            while ((en = readdir(dr)) != NULL) {
                bool fileCSV = isCSV(en->d_name);
                if (fileCSV){
                    cout << "CSV: " << en->d_name << endl;
                    addWordToTrie(&root, removeExtension(en->d_name));// add to trie
                }
            }
        }
      }
      closedir(dr); //close all directory
   }
   else{
    cout << "Failed to open directory ../index" << endl;
   }
}

