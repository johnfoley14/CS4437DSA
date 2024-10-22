#include <iostream>
#include <vector>

#include "HashMap.h"

const double MAX_LOAD_FACTOR = 0.7;

template <typename KeyType, typename ValueType>
HashMap<KeyType, ValueType>::HashMap(size_t size)
    : tableSize(size), numElements(0) {
      table = new DynamicArray<Entry>;
    }

template <typename KeyType, typename ValueType>
HashMap<KeyType, ValueType>::~HashMap() {
  delete table;
  // will be needed when we use our LinkedList instead of vector
}

template <typename KeyType, typename ValueType>
size_t HashMap<KeyType, ValueType>::hashFunction(const KeyType& key) const {
  std::hash<KeyType> hashFn;  // change me to custom/ md-5
  return hashFn(key) % tableSize;
}

template <typename KeyType, typename ValueType>
size_t HashMap<KeyType, ValueType>::findSlot(const KeyType& key) const {
  size_t index = hashFunction(key);
  size_t originalIndex = index;
  size_t i = 0;

  while (table->get(index).isActive ||
         table->get(index).isDeleted) {  // available slot
    if (table->get(index).isActive && table->get(index).key == key) {
      return index;
    }

    // (h(k) + i + i^2) % tableSize
    i++;
    index = (originalIndex + i + (i * i)) % tableSize;

    if (index == originalIndex) {  // table full, rehash
      break;
    }
  }

  return index;
}

template <typename KeyType, typename ValueType>
void HashMap<KeyType, ValueType>::rehash() {
  DynamicArray<Entry>* oldTable = table;

  table->resize();
  for (int i = 0; i < table->getSize(); ++i) {
    table->insert(i, Entry());  // Reset each entry
  }

  numElements = 0;

  // Reinsert all active entries from oldTable
  for (int i = 0; i < oldTable->getSize(); ++i) {
    const auto& entry = oldTable->get(i);
    if (entry.isActive) {
      insert(entry.key, entry.value);
    }
  }
}

template <typename KeyType, typename ValueType>
void HashMap<KeyType, ValueType>::insert(const KeyType& key,
                                         const ValueType& value) {
  if (numElements >= tableSize * MAX_LOAD_FACTOR) {
    // Rehash if the load factor exceeds the threshold
    cout << "Rehashing the table..." << endl;
    rehash();
  }

  size_t index = findSlot(key);

  if (!table->get(index).isActive ||
      table->get(index).isDeleted) {  // available slot
    Entry newEntry = table->get(index);
    newEntry.key = key;
    newEntry.value = value;
    newEntry.isActive = true;
    newEntry.isDeleted = false;

    table->insert(index, newEntry);

    numElements++;
  } else {  // key already exists
    Entry newEntry;
    newEntry.value->count = value->count;
    newEntry.value->positions = value->positions;
    table->insert(index, newEntry);
  }
}

template <typename KeyType, typename ValueType>
bool HashMap<KeyType, ValueType>::get(const KeyType& key,
                                      ValueType& value) const {
  size_t index = hashFunction(key);
  size_t originalIndex = index;
  size_t i = 0;

  while (table->get(index).isActive || table->get(index).isDeleted) {
    if (table->get(index).isActive && table->get(index).key == key) {
      value = table->get(index).value;  // Set the value
      return true;
    }
    // probing for next slot
    i++;
    index = (originalIndex + i + i * i) % tableSize;

    if (index == originalIndex) {  // key not found
      break;
    }
  }

  return false;  // Key not found
}

template <typename KeyType, typename ValueType>
void HashMap<KeyType, ValueType>::remove(const KeyType& key) {
  size_t index = hashFunction(key);
  size_t originalIndex = index;
  size_t i = 0;

  while (table->get(index).isActive || table->get(index).isDeleted) {
    if (table->get(index).isActive && table->get(index).key == key) {
      table->get(index).isActive = false;
      table->get(index).isDeleted = true;
      numElements--;
      return;
    }
    // probing for next slot
    i++;
    index = (originalIndex + i + i * i) % tableSize;

    if (index == originalIndex) {  // key not found
      break;
    }
  }
}

template <typename KeyType, typename ValueType>
LinkedList<pair<KeyType, ValueType>> HashMap<KeyType, ValueType>::getAll()
    const {
  LinkedList<pair<KeyType, ValueType>> allEntries;
  for (int i = 0; i < table->getSize(); ++i) {
    const auto& entry = table->get(i);
    cout << "Last line?" << endl;
    cout << "is activr" << entry.isActive << endl;
    if (entry.isActive) {
      allEntries.append({entry.key, entry.value});
    }
  }
  return allEntries;
}
