#pragma once

template <typename T>
struct BinaryTreeNode{

    public:
        BinaryTreeNode();
        BinaryTreeNode(const T &);
        BinaryTreeNode(const BinaryTreeNode *&);
        ~BinaryTreeNode();
        BinaryTreeNode *&operator =(const BinaryTreeNode *&);

        void insert(const T &);

        BinaryTreeNode *left, *right;
        T value;

    private:
        void free();
        void copy(const BinaryTreeNode *&);

};

template <typename T>
BinaryTreeNode<T>::BinaryTreeNode(): left(nullptr), right(nullptr), value(T()){}

template <typename T>
BinaryTreeNode<T>::BinaryTreeNode(const T &value): left(nullptr), right(nullptr), value(value){}

template <typename T>
BinaryTreeNode<T>::BinaryTreeNode(const BinaryTreeNode *&other){ this -> copy(other); }

template <typename T>
BinaryTreeNode<T>::~BinaryTreeNode(){ this -> free(); }

template <typename T>
BinaryTreeNode<T> *&BinaryTreeNode<T>::operator =(const BinaryTreeNode<T> *&other){

    if(this != &other){

        this -> free();
        this -> copy(other);

    }

    return *this;

}

template <typename T>
void BinaryTreeNode<T>::insert(const T &value){
    
    if(this -> value > value)
        if(this -> left != nullptr) this -> left -> insert(value);
        else this -> left = new BinaryTreeNode<T>(value);
    else
        if(this -> right != nullptr) this -> right -> insert(value);
        else this -> right = new BinaryTreeNode<T>(value);
    
}

template <typename T>
void BinaryTreeNode<T>::free(){ delete this -> left; delete this -> right; }

template <typename T>
void BinaryTreeNode<T>::copy(const BinaryTreeNode * &other){

    this -> left = other.left -> clone();
    this -> right = other.right -> clone();
    this -> value = other.value;

}