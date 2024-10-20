#ifndef TRIE_H
#define TRIE_H

#include <string>
#include <dirent.h> // handles directories
#include <iostream>
#include <vector> 
#include "DynamicArray.h"

struct TrieNode {
    char letter;
    TrieNode* children[26];
    bool isLeaf;

    TrieNode(); 
    ~TrieNode();
};

// Function declarations
bool isCSV(const std::string& filename);
std::string removeExtension(const std::string& filename);
void addWordToTrie(TrieNode* root, const std::string& word);
TrieNode* findNode(TrieNode* root, const std::string& partial);
void findWords(TrieNode* node, const std::string& partial, DynamicArray<std::string>& words);
DynamicArray<std::string> searchTrie(TrieNode* root, const std::string& partial);
void findFileAndAddToTrie(TrieNode &root);

#endif 
