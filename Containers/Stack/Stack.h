#pragma once

#include <stdexcept>

using std::out_of_range;

typedef unsigned long long int size_t;

template <typename T>
class Stack{

    public:
        Stack();
        Stack(const Stack<T> &);
        Stack(Stack<T> &&);
        ~Stack();
        Stack<T> &operator =(const Stack<T> &);
        Stack<T> &operator =(Stack<T> &&);

        bool empty() const;
        size_t size() const;
        T back();
        const T back() const;
        void push_back(const T &);
        T pop_back();

    private:
        T *S;
        size_t SIZE, CAPACITY;

        void free();
        void copy(const Stack<T> &);
        void resize();

};

template <typename T>
Stack<T>::Stack(): SIZE(0), CAPACITY(1){ this -> S = new T[this -> CAPACITY]; }

template <typename T>
Stack<T>::Stack(const Stack<T> &other){ this -> copy(other); }

template <typename T>
Stack<T>::Stack(Stack<T> &&other){

    this -> SIZE = other.SIZE;
    this -> CAPACITY = other.CAPACITY;
    this -> S = other.S;
    other.S = nullptr;

}

template <typename T>
Stack<T>::~Stack(){ this -> free(); }

template <typename T>
Stack<T> &Stack<T>::operator =(const Stack<T> &other){

    if(this != &other){

        this -> free();
        this -> copy(other);

    }
    
    return *this;

}

template <typename T>
Stack<T> &Stack<T>::operator =(Stack<T> &&other){

    if(this != &other){

        this -> free();
        this -> SIZE = other.SIZE;
        this -> CAPACITY = other.CAPACITY;
        this -> S = other.S;
        other.S = nullptr;

    }

    return *this;

}

template <typename T>
bool Stack<T>::empty() const{ return !this -> SIZE; }

template <typename T>
size_t Stack<T>::size() const{ return this -> SIZE; }

template <typename T>
T Stack<T>::back(){
    
    if(!this -> SIZE) throw out_of_range("Stack is empty");
    return this -> S[this -> SIZE - 1];
    
}

template <typename T>
const T Stack<T>::back() const{
    
    if(!this -> SIZE) throw out_of_range("Stack is empty");
    return this -> S[this -> SIZE - 1];
    
}

template <typename T>
void Stack<T>::push_back(const T &element){

    this -> resize();
    this -> S[this -> SIZE++] = element;

}

template <typename T>
T Stack<T>::pop_back(){

    if(this -> isEmpty()) throw out_of_range("Stack is empty");

    T result = this -> S[--this -> SIZE];
    this -> S[this -> SIZE].~T();
    this -> resize();

    return result;

}

template <typename T>
void Stack<T>::free(){ delete[] this -> S; }

template <typename T>
void Stack<T>::copy(const Stack<T> &other){

    this -> SIZE = other.SIZE;
    this -> CAPACITY = other.CAPACITY;
    this -> S = new T[other.CAPACITY];
    for(size_t i = 0; i < other.SIZE; i++)
        this -> S[i] = other.S[i];

}

template <typename T>
void Stack<T>::resize(){

    if(this -> SIZE < this -> CAPACITY / 4) this -> CAPACITY /= 2;
    else if(this -> SIZE == this -> CAPACITY) this -> CAPACITY *= 2;
    else return;

    T *temp = this -> V;
    this -> V = new T[this -> CAPACITY];
    for(size_t i = 0; i < this -> SIZE; i++)
        this -> S[i] = temp[i];
    delete[] temp;

}