#include <gtest/gtest.h>
#include "trie.h"
#include "DynamicArray.h"


TEST(TrieTest, TrieNodeCreation)
{
    TrieNode *trieNode = new TrieNode();
    ASSERT_NE(trieNode, nullptr);
    delete trieNode;
}

TEST(TrieTest, TrieNodeDeletion)
{
    TrieNode *trieNode = new TrieNode();
    delete trieNode;
}


TEST(TrieTest, AddCharToTrie)
{
    TrieNode *trieNode = new TrieNode();
    addWordToTrie(trieNode, "a");
    EXPECT_EQ(trieNode->children['a' - 'a']->letter, 'a');   
    delete trieNode;
}


TEST(TrieTest, AddWordToTrie)
{
    TrieNode *trieNode = new TrieNode();
    addWordToTrie(trieNode, std::string("apple"));
    TrieNode *curr = trieNode;
    for (char c : std::string("apple"))
    {
        curr = curr->children[c - 'a'];
    }
    EXPECT_EQ(curr->isLeaf, true);
    delete trieNode;
}


TEST(TrieTest, RemoveExtension)
{
    std::string filename = "apple.csv";
    std::string filenameWithoutExtension = removeExtension(filename);
    EXPECT_EQ(filenameWithoutExtension, "apple");
}


TEST(TrieTest, IsCSV)
{
    std::string filename = "apple.csv";
    bool isCSVFile = isCSV(filename);
    EXPECT_EQ(isCSVFile, true);
}

// searching
TEST(TrieTest, SearchingPartialWord){
    TrieNode *trieNode = new TrieNode();
    
    // Adding words to the trie
    addWordToTrie(trieNode, "apple");
    addWordToTrie(trieNode, "app");
    addWordToTrie(trieNode, "apples");

    DynamicArray<std::string> words = searchTrie(trieNode, "app");

    int size = words.getSize();
    EXPECT_EQ(size, 3);  

    delete trieNode;  
}

TEST(TrieTest, SearchingFullWord){
    TrieNode *trieNode = new TrieNode();
    
    addWordToTrie(trieNode, "apple");
    addWordToTrie(trieNode, "app");
    addWordToTrie(trieNode, "apples");

    DynamicArray<std::string> words = searchTrie(trieNode, "apples");
    DynamicArray<std::string> answer;
    answer.add("apples");

    EXPECT_EQ(answer, words);  // overloaded == operator

    delete trieNode;  
}

TEST(TrieTest, SearchingNonExistentWord){
    TrieNode *trieNode = new TrieNode();
    
    addWordToTrie(trieNode, "apple");
    addWordToTrie(trieNode, "app");
    addWordToTrie(trieNode, "apples");

    DynamicArray<std::string> words = searchTrie(trieNode, "orange");

    int size = words.getSize();
    EXPECT_EQ(size,0);  

    delete trieNode;  
}

TEST(TrieTest, CheckLeafNodes) {
    TrieNode *trieNode = new TrieNode();
    addWordToTrie(trieNode, "cat");
    addWordToTrie(trieNode, "catalog");

    EXPECT_EQ(trieNode->children['c' - 'a']->children['a' - 'a']->children['t' - 'a']->isLeaf, true);
    EXPECT_EQ(trieNode->children['c' - 'a']->children['a' - 'a']->children['t' - 'a']->children['a' - 'a']->isLeaf, false); // "cata" - not word

    delete trieNode;
}

TEST(TrieTest, AddEmptyWord) {
    TrieNode *trieNode = new TrieNode();
    addWordToTrie(trieNode, "");  

    EXPECT_EQ(trieNode->isLeaf, true);  

    delete trieNode;
}
