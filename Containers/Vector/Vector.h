#pragma once

#include <fstream>
#include <stdexcept>

using std::out_of_range;
using std::ostream;
using std::ofstream;
using std::ifstream;

template <typename T>
class Vector{
    
    public:
        Vector();
        Vector(const Vector<T> &);
        Vector(Vector<T> &&);
        ~Vector();

        T &operator [](const size_t &);
        const T &operator [](const size_t &) const;
        Vector<T> &operator =(const Vector<T> &);
        Vector<T> &operator =(Vector<T> &&);
        template <typename U> friend ostream &operator <<(ostream &os, const Vector<U> &);

        const bool isEmpty() const;
        const bool contains(const T &) const;
        const size_t capacity() const;
        const size_t size() const;
        const size_t getIndex(const T &) const;
        T getAt(const size_t &) const;
        T getFirst() const;
        T getLast() const;
        T popBack();
        T removeAt(size_t &);
        void pushBack(const T &);
        void write(ofstream &) const;
        void read(ifstream &);
        void insert(const size_t &, const T &);
        void erase(const T &);

    private:
        T *V;
        size_t SIZE, CAPACITY;
        
        void resize();
        void free();
        void copy(const Vector<T> &);

};

template <typename T>
Vector<T>::Vector(): SIZE(0), CAPACITY(1){ this -> V = new T[this -> CAPACITY]; }

template <typename T>
Vector<T>::Vector(const Vector<T> &other){ this -> copy(other); }

template <typename T>
Vector<T>::Vector(Vector<T> &&other): V(other.V), SIZE(other.SIZE), CAPACITY(other.CAPACITY){ other.V = nullptr; }

template <typename T>
Vector<T>::~Vector(){ this -> del(); }

template <typename T>
T &Vector<T>::operator [](const size_t &index){
    
    if(index >= this -> SIZE) throw out_of_range("");
    return this -> V[index];
    
}

template <typename T>
const T &Vector<T>::operator [](const size_t &index) const{
    
    if(index >= this -> SIZE) throw out_of_range("");
    return this -> V[index];
    
}

template <typename T>
Vector<T> &Vector<T>::operator =(const Vector<T> &other){

    if(this != &other){

        this -> free();
        this -> copy(other);

    }

    return *this;

}

template <typename T>
Vector<T> &Vector<T>::operator =(Vector<T> &&other){

    if(this != &other){

        this -> free();
        this -> CAPACITY = other.CAPACITY;
        this -> SIZE = other.SIZE;
        this -> V = other.V;
        other.V = nullptr;

    }

    return *this;

}

template <typename T>
ostream &operator <<(ostream &os, const Vector<T> &obj){

    for(size_t i = 0; i < obj.size(); i++){

        if(i != 0) os << ' ';
        os << obj[i];

    }

    return os;

}

template <typename T>
const bool Vector<T>::isEmpty() const{ return this -> SIZE == 0; }

template <typename T>
const bool Vector<T>::contains(const T &search) const{

    for(size_t i = 0; i < this -> SIZE; i++)
        if(this -> V[i] == search) return true;
    return false;
    
}

template <typename T>
const size_t Vector<T>::capacity() const{ return this -> CAPACITY; }

template <typename T>
const size_t Vector<T>::size() const{ return this -> SIZE; }

template <typename T>
const size_t Vector<T>::getIndex(const T &element) const{

    for(int i = 0; i < this -> SIZE; i++)
        if(this -> V[i] == element)
            return i;

    return -1;

}

template <typename T>
T Vector<T>::getAt(const size_t &index) const{

    if(index >= this -> SIZE) throw out_of_range("Index out of range");
    return this -> V[index];

}

template <typename T>
T Vector<T>::getFirst() const{

    if(this -> isEmpty()) throw out_of_range("Index out of range");
    return this -> V[0];

}

template <typename T>
T Vector<T>::getLast() const{
    
    if(this -> isEmpty()) throw out_of_range("Index out of range");
    return this -> V[SIZE - 1];
    
}

template <typename T>
T Vector<T>::popBack(){

    if(this -> isEmpty()) throw out_of_range("Index out of range");
    T result = this -> V[--this -> SIZE];
    delete this -> V[this -> SIZE];
    this -> resize();

    return result;

}

template <typename T>
T Vector<T>::removeAt(size_t &index){

    if(index >= this -> SIZE) throw out_of_range("Index out of range");
    T element = this -> V[index];
    --this -> SIZE;
    for(; index < this -> SIZE; index++) this -> V[index] = this -> V[index + 1];
    delete this -> V[this -> SIZE];
    this -> resize();

    return element;

}

template <typename T>
void Vector<T>::pushBack(const T &element){

    this -> resize();
    this -> V[this -> SIZE++] = element;

}

template <typename T>
void Vector<T>::write(ofstream &ofs) const{

    ofs.write((const char *)&this -> CAPACITY, sizeof(size_t));
    ofs.write((const char *)&this -> SIZE, sizeof(size_t));
    for(size_t i = 0; i < this -> SIZE; i++)
        ofs.write((const char *)&this -> V[i], sizeof(T));

}

template <typename T>
void Vector<T>::read(ifstream &ifs){

    ifs.read((char *)&this -> CAPACITY, sizeof(size_t));
    ifs.read((char *)&this -> SIZE, sizeof(size_t));
    this -> V = new T[this -> CAPACITY];
    for(size_t i = 0; i < this -> SIZE; i++)
        ifs.read((char *)&this -> V[i], sizeof(T));

}

template <typename T>
void Vector<T>::insert(const size_t &index, const T &element){

    this -> resize();
    if(index > this -> SIZE) throw out_of_range("Index out of range");
    for(size_t j = this -> SIZE++; j >= index; j--) this -> V[j + 1] = this -> V[j];
    this -> V[index] = element;

}

template <typename T>
void Vector<T>::erase(const T &element){

    size_t offset = 0;

    for(size_t i = 0; i < this -> SIZE; i++){

        while(this -> V[i + offset] == element) offset++;
        this -> V[i] = this -> V[i + offset];

    }

    this -> SIZE -= offset;
    this -> resize();

}

template <typename T>
void Vector<T>::resize(){

    if(this -> SIZE < this -> CAPACITY / 4) this -> CAPACITY /= 2;
    else if(this -> SIZE == this -> CAPACITY) this -> CAPACITY *= 2;
    else return;

    T *temp = this -> V;
    this -> V = new T[this -> CAPACITY];
    copy(temp, temp + this -> SIZE, this -> V);
    delete[] temp;

}

template <typename T>
void Vector<T>::free(){ delete[] this -> V; }

template <typename T>
void Vector<T>::copy(const Vector<T> &other){

    this -> CAPACITY = other.CAPACITY;
    this -> SIZE = other.SIZE;
    this -> V = new T[other.CAPACITY];
    for(size_t i = 0; i < other.SIZE; i++)
        this -> V[i] = other.V[i];

}