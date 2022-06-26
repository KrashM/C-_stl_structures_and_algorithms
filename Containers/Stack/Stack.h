#pragma once

#include <stdexcept>

using std::out_of_range;

typedef unsigned long long int size_t;

template <typename T>
class stack{

    public:
        stack();
        stack(const stack<T> &);
        stack(stack<T> &&);
        ~stack();
        stack<T> &operator =(const stack<T> &);
        stack<T> &operator =(stack<T> &&);

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
        void copy(const stack<T> &);
        void resize();

};

template <typename T>
stack<T>::stack(): SIZE(0), CAPACITY(1){ this -> S = new T[this -> CAPACITY]; }

template <typename T>
stack<T>::stack(const stack<T> &other){ this -> copy(other); }

template <typename T>
stack<T>::stack(stack<T> &&other){

    this -> SIZE = other.SIZE;
    this -> CAPACITY = other.CAPACITY;
    this -> S = other.S;
    other.S = nullptr;

}

template <typename T>
stack<T>::~stack(){ this -> free(); }

template <typename T>
stack<T> &stack<T>::operator =(const stack<T> &other){

    if(this != &other){

        this -> free();
        this -> copy(other);

    }
    
    return *this;

}

template <typename T>
stack<T> &stack<T>::operator =(stack<T> &&other){

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
bool stack<T>::empty() const{ return !this -> SIZE; }

template <typename T>
size_t stack<T>::size() const{ return this -> SIZE; }

template <typename T>
T stack<T>::back(){
    
    if(!this -> SIZE) throw out_of_range("stack is empty");
    return this -> S[this -> SIZE - 1];
    
}

template <typename T>
const T stack<T>::back() const{
    
    if(!this -> SIZE) throw out_of_range("stack is empty");
    return this -> S[this -> SIZE - 1];
    
}

template <typename T>
void stack<T>::push_back(const T &element){

    this -> resize();
    this -> S[this -> SIZE++] = element;

}

template <typename T>
T stack<T>::pop_back(){

    if(this -> isEmpty()) throw out_of_range("stack is empty");

    T result = this -> S[--this -> SIZE];
    this -> S[this -> SIZE].~T();
    this -> resize();

    return result;

}

template <typename T>
void stack<T>::free(){ delete[] this -> S; }

template <typename T>
void stack<T>::copy(const stack<T> &other){

    this -> SIZE = other.SIZE;
    this -> CAPACITY = other.CAPACITY;
    this -> S = new T[other.CAPACITY];
    for(size_t i = 0; i < other.SIZE; i++)
        this -> S[i] = other.S[i];

}

template <typename T>
void stack<T>::resize(){

    if(this -> SIZE < this -> CAPACITY / 4) this -> CAPACITY /= 2;
    else if(this -> SIZE == this -> CAPACITY) this -> CAPACITY *= 2;
    else return;

    T *temp = this -> V;
    this -> V = new T[this -> CAPACITY];
    for(size_t i = 0; i < this -> SIZE; i++)
        this -> S[i] = temp[i];
    delete[] temp;

}