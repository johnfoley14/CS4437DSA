#ifndef AVL_TREE_MAP_H
#define AVL_TREE_MAP_H

template <typename KType, typename VType>
struct AVLNode {
    KType key;
    VType value;
    AVLNode<KType, VType>* left;
    AVLNode<KType, VType>* right;
    int height;
  
    AVLNode(KType k, VType v);
    ~AVLNode();

    int getBalance();
    int heighOfTree();
};

template <typename KType, typename VType>
class AVLTreeMap {
public:
    AVLNode<KType, VType>* root;

    AVLTreeMap() : root(nullptr) {}
    ~AVLTreeMap() { delete root; }

    AVLNode<KType, VType>* insert(AVLNode<KType, VType>* node, const KType &key, const VType &value);
    AVLNode<KType, VType>* rightRotate(AVLNode<KType, VType>* y);
    AVLNode<KType, VType>* leftRotate(AVLNode<KType, VType>* x);
    AVLNode<KType, VType>* search(const KType& key) const;
    
};

#include "AVLTreeMap.tpp"

#endif // AVL_TREE_MAP_H
