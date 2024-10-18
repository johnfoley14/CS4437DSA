#ifndef TRIE_H
#define TRIE_H

#include <string>
#include <dirent.h> // handles directories
#include <iostream>
#include <vector> 

struct TrieNode {
    char letter;
    TrieNode* children[26];
    bool isLeaf;

    TrieNode(); 
};

// Function declarations
bool isCSV(const std::string& filename);
std::string removeExtension(const std::string& filename);
void addWordToTrie(TrieNode* root, const std::string& word);
TrieNode* findNode(TrieNode* root, const std::string& partial);
void findWords(TrieNode* node, const std::string& partial, std::vector<std::string>& words);
std::vector<std::string> searchTrie(TrieNode* root, const std::string& partial);
void findFileAndAddToTrie(TrieNode &root);

#endif 
