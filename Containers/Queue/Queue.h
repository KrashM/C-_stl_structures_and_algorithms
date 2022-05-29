#pragma once

#include <stdexcept>

using std::out_of_range;

typedef unsigned long long int size_t;

template <typename T>
class Queue{

    public:
        Queue();
        Queue(const Queue<T> &);
        Queue(Queue<T> &&);
        ~Queue();
        Queue<T> &operator =(const Queue<T> &);
        Queue<T> &operator =(Queue<T> &&);

        bool isEmpty() const;
        size_t size() const;
        void enqueue(T x);
        T dequeue();
        T front();
        const T front() const;

    
    private:
        T *Q;
        size_t SIZE, CAPACITY;
        long long FRONT, REAR;

        void resize();
        void copy(const Queue<T> &);
        void free();

};

template <typename T>
Queue<T>::Queue(): SIZE(0), CAPACITY(1), FRONT(-1), REAR(-1){ this -> Q = new T[this -> CAPACITY]; }
template <typename T>
Queue<T>::Queue(const Queue<T> &other){ this -> copy(other); }
template <typename T>
Queue<T>::Queue(Queue<T> &&other){

    this -> CAPACITY = other.CAPACITY;
    this -> SIZE = other.SIZE;
    this -> Q = other.Q;
    other.Q = nullptr;

}
template <typename T>
Queue<T>::~Queue(){ this -> free(); }

template <typename T>
Queue<T> &Queue<T>::operator =(const Queue<T> &other){

    if(this != &other){

        this -> free();
        this -> copy(other);

    }

    return *this;

}

template <typename T>
Queue<T> &Queue<T>::operator =(Queue<T> &&other){

    if(this != &other){

        this -> free();
        this -> CAPACITY = other.CAPACITY;
        this -> SIZE = other.SIZE;
        this -> Q = other.Q;
        other.Q = nullptr;

    }

    return *this;

}

template <typename T>
bool Queue<T>::isEmpty() const{ return front == -1 && rear == -1; }

template <typename T>
size_t Queue<T>::size() const{ return this -> SIZE; }

template <typename T>
void Queue<T>::enqueue(T element){

    this -> resize();
    this -> FRONT = 0;
    Q[this -> REAR++] = element;

}

template <typename T>
T Queue<T>::dequeue(){

    if(this -> isEmpty()) throw out_of_range("Queue is empty");

    T result = this -> Q[this -> FRONT];

    if(this -> FRONT == this -> REAR) this -> REAR = this -> FRONT = -1;
    else this -> Q[this -> FRONT] = this -> Q[this -> FRONT + 1];

    this -> resize();

    return result;

}

template <typename T>
T Queue<T>::front(){

    if(this -> FRONT == -1) throw out_of_range("Queue is empty");
    return this -> Q[this -> FRONT];

}

template <typename T>
const T Queue<T>::front() const{

    if(this -> FRONT == -1) throw out_of_range("Queue is empty");
    return this -> Q[this -> FRONT];

}

template <typename T>
void Queue<T>::resize(){

    if(this -> SIZE < this -> CAPACITY / 4) this -> CAPACITY /= 2;
    else if(this -> SIZE == this -> CAPACITY) this -> CAPACITY *= 2;
    else return;

    T *temp = this -> Q;
    this -> Q = new T[this -> CAPACITY];
    for(size_t i = 0; i < this -> SIZE; i++)
        this -> Q[i] = temp[i];
    delete[] temp;

}

template <typename T>
void Queue<T>::copy(const Queue<T> &other){

    this -> CAPACITY = other.CAPACITY;
    this -> SIZE = other.SIZE;
    this -> FRONT = other.FRONT;
    this -> REAR = other.REAR;

    this -> Q = new T[other.CAPCITY];
    for(size_t i = 0; i < other.SIZE; i++)
        this -> Q[i] = other.Q[i];

}

template <typename T>
void Queue<T>::free(){ delete[] this -> Q; }