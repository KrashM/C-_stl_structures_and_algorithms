#pragma once

#include <string>
#include "BinaryTreeNode.h"

using std::string;
using std::to_string;

template <typename T>
class BinaryTree{

    public:
        BinaryTree();
        BinaryTree(const T &);
        BinaryTree(const BinaryTree &);
        ~BinaryTree();

        BinaryTree &operator =(const BinaryTree &);

        void insert(const T &);
        const string toString() const;
        bool search(const T &) const;

    private:
        void free();
        void copy(const BinaryTree &);
        void inorder(const BinaryTreeNode<T> * const &, string &) const;
        bool binarySearch(const BinaryTreeNode<T> * const &, const T &) const;

        BinaryTreeNode<T> *root;

};

template <typename T>
BinaryTree<T>::BinaryTree(): root(new BinaryTreeNode<T>()){}

template <typename T>
BinaryTree<T>::BinaryTree(const T &value): root(new BinaryTreeNode<T>(value)){}

template <typename T>
BinaryTree<T>::BinaryTree(const BinaryTree<T> &other){ this -> copy(other); }

template <typename T>
BinaryTree<T>::~BinaryTree(){ this -> free(); }

template <typename T>
BinaryTree<T> &BinaryTree<T>::operator =(const BinaryTree<T> &other){

    if(this != &other){

        this -> free();
        this -> copy(other);

    }

    return *this;

}

template <typename T>
void BinaryTree<T>::insert(const T &value){
    
    if(root != nullptr) this -> root -> insert(value);
    else this -> root = new BinaryTreeNode<T>(value);
    
}

template <typename T>
const string BinaryTree<T>::toString() const{
    
    string result = "";
    this -> inorder(this -> root, result);
    result.erase(result.begin() + result.length() - 1);
    return result;
    
}

template <typename T>
bool BinaryTree<T>::search(const T &value) const{ return this -> binarySearch(this -> root, value); }

template <typename T>
bool BinaryTree<T>::binarySearch(const BinaryTreeNode<T> * const &root, const T &value) const{

    if(root == nullptr) return false;
    if(root -> value == value) return true;

    if(root -> value > value) return this -> binarySearch(root -> left, value);
    return this -> binarySearch(root -> right, value);

}

template <typename T>
void BinaryTree<T>::free(){ delete this -> root; }

template <typename T>
void BinaryTree<T>::copy(const BinaryTree<T> &other){

    this -> rootValue = other.rootValue;
    this -> root = other.root -> clone();

}

template <typename T>
void BinaryTree<T>::inorder(const BinaryTreeNode<T> * const &root, string &result) const{

    if(root == nullptr) return;

    inorder(root -> left, result);
    result += to_string(root -> value) + " ";
    inorder(root -> right, result);

}