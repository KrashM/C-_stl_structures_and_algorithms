#pragma once

template <typename T, typename U>
struct Pair{

    T first;
    U second;

    Pair();
    Pair(const T &, const U &);
    Pair(const Pair<T, U> &);
    Pair &operator =(const Pair<T, U> &);

    void swap(Pair<T, U> &);

    private: void copy(const Pair<T, U> &);

};

template<typename T, typename U>
Pair<T, U>::Pair(): first(T()), second(U()){}

template<typename T, typename U>
Pair<T, U>::Pair(const T &first, const U &second): first(first), second(second){}

template<typename T, typename U>
Pair<T, U>::Pair(const Pair<T, U> &other){ this -> copy(other); }

template<typename T, typename U>
Pair<T, U> &Pair<T, U>::operator =(const Pair<T, U> &other){

    if(this != &other) this -> copy(other);
    return *this;

}

template<typename T, typename U>
void Pair<T, U>::swap(Pair<T, U> &other){

    T tempT = this -> first;
    U tempU = this -> second;

    this -> first = other.first;
    this -> second = other.second;

    other.first = tempT;
    other.second = tempU;

}

template<typename T, typename U>
void Pair<T, U>::copy(const Pair<T, U> &other){

    this -> first = other.first;
    this -> second = other.second;

}