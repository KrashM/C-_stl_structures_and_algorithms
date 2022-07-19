#include "../Vector/vector.h"
#include "../Pair/pair.h"

template <typename Key, typename T>
class dictionary{

    public:
        dictionary();
        dictionary(const dictionary<Key, T> &);
        dictionary(const dictionary<Key, T> &&);
        ~dictionary();

        dictionary &operator =(const dictionary<Key, T> &);
        dictionary &operator =(dictionary<Key, T> &&);

        pair<Key, T> &operator [](const Key &);
        const pair<Key, T> &operator [](const Key &) const;

        bool empty() const;
        size_t size() const;

        void insert(const pair<Key, T> &);

    private:
        void copy(const dictionary<Key, T> &);

        vector<pair<Key, T>> dict;

};


template <typename Key, typename T>
dictionary<Key, T>::dictionary(){}

template <typename Key, typename T>
dictionary<Key, T>::dictionary(const dictionary<Key, T> &other){ this -> copy(other); }

template <typename Key, typename T>
dictionary<Key, T>::dictionary(const dictionary<Key, T> &&other){ dict.move(other); }

template <typename Key, typename T>
dictionary<Key, T>::~dictionary(){}

template <typename Key, typename T>
dictionary<Key, T> &dictionary<Key, T>::operator =(const dictionary<Key, T> &other){

    if(this != &other){

        this -> free();
        this -> copy(other);

    }

}

template <typename Key, typename T>
dictionary<Key, T> &dictionary<Key, T>::operator =(dictionary<Key, T> &&other){

    if(this != &other) this -> dict = move(other.dict);

    return *this;

}


template <typename Key, typename T>
pair<Key, T> &dictionary<Key, T>::operator [](const Key &key){ return dict[key]; }

template <typename Key, typename T>
const pair<Key, T> &dictionary<Key, T>::operator [](const Key &key) const{ return dict[index]; }


template <typename Key, typename T>
bool dictionary<Key, T>::empty() const{ return !this -> dict.size(); }

template <typename Key, typename T>
size_t dictionary<Key, T>::size() const{ return this -> dict.size(); }

template <typename Key, typename T>
void dictionary<Key, T>::insert(const pair<Key, T> &element){

    // for(size_t i = 0; i < this -> dict.size(); i++)
    //     if()

}

template <typename Key, typename T>
void dictionary<Key, T>::copy(const dictionary<Key, T> &other){}