#ifndef HASHMAP_H
#define HASHMAP_H

#include <vector>
#include <functional> // std::hash

using namespace std;

template <typename KeyType, typename ValueType>
class HashMap {
private:
    struct Entry {
        KeyType key;
        ValueType value; // of type ValueType (Metadata)
        bool isActive;
        bool isDeleted;

        Entry() : key(), value(), isActive(false), isDeleted(false) {}
    };

    vector<Entry> table;
    size_t tableSize;
    size_t numElements;

    size_t hashFunction(const KeyType& key) const;
    size_t findSlot(const KeyType& key) const;
    void rehash();

public:
    HashMap(size_t size = 100000);
    ~HashMap();

    void insert(const KeyType& key, const ValueType& value);
    bool get(const KeyType& key, ValueType& value) const;
    void remove(const KeyType& key);
    vector<pair<KeyType, ValueType>> getAll() const;
};

#include "HashMap.tpp"

#endif // HASHMAP_H
