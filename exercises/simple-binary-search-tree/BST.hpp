#ifndef BST_SOL_HPP
#define BST_SOL_HPP

#include <iostream>
#include <vector>
#include <algorithm>

template <typename T>
class BST {
public:
    class Node {
    public:
        T key;
        Node* left {nullptr};
        Node* right {nullptr};
        Node* parent {nullptr};
        // Default constructor.
        Node(){}
        // Constructor that sets key and parent node.
        // You can also call this constructor with just the first argument and the second argument will default to nullptr.
        Node(T k, Node* node = nullptr) {
            key = k;
            parent = node;
        }
    };

private: 
    Node* root_ = nullptr;
    unsigned int size_ = 0;

public:
    // Default constructor.
    BST(); 

    // Destructor
    ~BST();

    // Insert a new key into the tree. We will maintain a set of keys, if the argument k is already in the tree then no action is taken.
    void insert(T k);

    // Search the tree for key k. Return a pointer to the node holding the key if it is in the tree, and nullptr otherwise.
    Node* find(T k);

    // Return a pointer to the node holding the minimum key in the tree.
    Node* min();

    // Make a vector with all keys in the tree ordered from smallest to largest, i.e. push back keys to the vector while doing an in-order traversal of the tree.
    std::vector<T> make_vec();

    // Return the number of elements in the tree.
    unsigned int size();

    // Return whether or not the tree is empty.
    bool empty();

private: 
    void delete_subtree(Node* node);

    void make_vec(Node* node, std::vector<T>& vec);

    // Assuming that node is not nullptr.
    Node* min(Node* node);
};

// Default constructor.
template <typename T>
BST<T>::BST(){} 

// Destructor.
template <typename T>
BST<T>::~BST() {
    delete_subtree(root_);
}

template <typename T>
void BST<T>::insert(T key) {
    // The node will iterate down through the tree starting from the root.
    Node* node = root_;
    // "prev_node" will hold node's parent.
    Node* prev_node = node;  
    bool went_right;

    if (node == nullptr) {
        root_ = new Node(key);
        ++size_;
        return;
    }

    while (node != nullptr) {
        prev_node = node;
        
        if (key < node->key) {
            node = node->left;
            went_right = false;
        } 

        else if (key > node->key) {
            node = node->right;
            went_right = true;
        } else {
            return;
        }
    }

    if (went_right) {
        prev_node->right = new Node(key, prev_node);
    } else {
        prev_node->left = new Node(key, prev_node);
    }

    ++size_;
}

template <typename T>
typename BST<T>::Node* BST<T>::find(T k) {
    Node* node = root_;

    while (node != nullptr && node->key != k) {
        node = k < node->key ?  node->left : node->right;
    }

    return node;  
}


template <typename T>
typename BST<T>::Node* BST<T>::min() {
    if (root_ == nullptr) {
        return root_;
    } else {
        return min(root_);
    }
}

template <typename T>
typename std::vector<T> BST<T>::make_vec() {
    std::vector<T> vec;
    vec.reserve(size_);
    make_vec(root_, vec);
    return vec;
}

template <typename T>
unsigned int BST<T>::size() {
    return size_;
}

template <typename T>
bool BST<T>::empty() {
    return (size_ == 0);
}

template <typename T>
void BST<T>::delete_subtree(Node* node) {
    if (node == nullptr) {
        return;
    }

    delete_subtree(node->left);
    delete_subtree(node->right);
    delete node;
}

template <typename T>
void BST<T>::make_vec(Node* node, std::vector<T>& vec) {
    if (node == nullptr) {
        return;
    }

    make_vec(node->left, vec);
    vec.push_back(node->key);
    make_vec(node->right, vec);
}

template <typename T>
typename BST<T>::Node* BST<T>::min(Node* node) {
    while (node->left != nullptr) {
        node = node->left;
    } 
    
    return node;
}

#endif