#include "AVLTreeMap.h"
#include <iostream>
#include <algorithm>

using namespace std;

template <typename KType, typename VType>
AVLNode<KType, VType>::AVLNode(KType k, VType v) {
    this->key = k;
    this->value = v;
    this->left = nullptr;
    this->right = nullptr;
    this->height = 1;
}

template <typename KType, typename VType>
AVLNode<KType, VType>::~AVLNode() {
    delete left;
    delete right;
}

template <typename KType, typename VType>
int AVLNode<KType, VType>::getBalance() {
    int leftHeight = (this->left) ? this->left->height : 0;
    int rightHeight = (this->right) ? this->right->height : 0;
    return leftHeight - rightHeight;
}


template <typename KType, typename VType>
AVLNode<KType, VType>* AVLTreeMap<KType, VType>::insert(AVLNode<KType, VType>* node, const KType &key, const VType &value) {
    // If the tree is empty
    if (node == nullptr) {
        return new AVLNode<KType, VType>(key, value);
    }
    // comparing the ASCII values of the key
    // Traverse to the left or right subtree
    if (key < node->key) {
        node->left = insert(node->left, key, value); 
    } else if (key > node->key) {
        node->right = insert(node->right, key, value);
    } else {
        node->value = value;  // Update the value if key already exists
        return node;
    }

    // updating height of the node
    node->height = 1 + max((node->left ? node->left->height : 0), (node->right ? node->right->height : 0));

    // Get the balance factor
    int balance = node->getBalance();

    // rotations
    // RR
    if (balance < -1 && key > node->right->key) {
        return leftRotate(node);
    }

    // LL
    if (balance > 1 && key < node->left->key) {
        return rightRotate(node);
    }

    // RL
    if (balance < -1 && key < node->right->key) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    // LR
    if (balance > 1 && key > node->left->key) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    return node;
}


template <typename KType, typename VType>
AVLNode<KType, VType>* AVLTreeMap<KType, VType>::rightRotate(AVLNode<KType, VType>* y) {
    AVLNode<KType, VType>* x = y->left; 
    AVLNode<KType, VType>* T2 = x->right;

    x->right = y; // new root 
    y->left = T2; 

    y->height = max(y->left ? y->left->height : 0, y->right ? y->right->height : 0) + 1;
    x->height = max(x->left ? x->left->height : 0, x->right ? x->right->height : 0) + 1;

    return x;  
}

template <typename KType, typename VType>
AVLNode<KType, VType>* AVLTreeMap<KType, VType>::leftRotate(AVLNode<KType, VType>* x) {
    AVLNode<KType, VType>* y = x->right;
    AVLNode<KType, VType>* T2 = y->left;

    y->left = x; //nwe root
    x->right = T2;

    x->height = max(x->left ? x->left->height : 0, x->right ? x->right->height : 0) + 1;
    y->height = max(y->left ? y->left->height : 0, y->right ? y->right->height : 0) + 1;

    return y;  
}

template <typename KType, typename VType>
AVLNode<KType, VType>* AVLTreeMap<KType, VType>::search(const KType& key) const {
    AVLNode<KType, VType>* current = root;

    while (current != nullptr) {
        if (key == current->key) {
            return current; // Node found
        } else if (key < current->key) {
            current = current->left; // Search in the left subtree
        } else {
            current = current->right; // Search in the right subtree
        }
    }

    return nullptr; // Node not found
}



