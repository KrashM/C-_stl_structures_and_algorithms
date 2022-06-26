#pragma once

template <typename T, typename U>
struct pair{

    T first;
    U second;

    pair();
    pair(const T &, const U &);
    pair(const pair<T, U> &);
    pair &operator =(const pair<T, U> &);

    void swap(pair<T, U> &);

    private: void copy(const pair<T, U> &);

};

template<typename T, typename U>
pair<T, U>::pair(): first(T()), second(U()){}

template<typename T, typename U>
pair<T, U>::pair(const T &first, const U &second): first(first), second(second){}

template<typename T, typename U>
pair<T, U>::pair(const pair<T, U> &other){ this -> copy(other); }

template<typename T, typename U>
pair<T, U> &pair<T, U>::operator =(const pair<T, U> &other){

    if(this != &other) this -> copy(other);
    return *this;

}

template<typename T, typename U>
void pair<T, U>::swap(pair<T, U> &other){

    T tempT = this -> first;
    U tempU = this -> second;

    this -> first = other.first;
    this -> second = other.second;

    other.first = tempT;
    other.second = tempU;

}

template<typename T, typename U>
void pair<T, U>::copy(const pair<T, U> &other){

    this -> first = other.first;
    this -> second = other.second;

}