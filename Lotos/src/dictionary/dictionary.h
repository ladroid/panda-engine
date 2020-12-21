//
// Created by Lado on 26/5/20.
//

#ifndef LOTOS_DICTIONARY_H
#define LOTOS_DICTIONARY_H

#include <iostream>
#include <algorithm>
#include <iterator>
#include <map>
#include "../object/object.h"

#define SIZE 16

template<typename K, typename V>
void print_map(std::map<K, V> const &m) {
    for(auto const &pair: m) {
        std::cout << "{" << pair.first << ": " << pair.second << "}\n";
    }
}

template<typename K, typename V>
class dictionary: object {
private:
    int size;
    K *array;
    std::map<K, V> arr;
    void ensureCapacity();
public:
    dictionary();
    dictionary(int s);
    void set(K elem, V val);
    void get();
    std::string getClass();
    bool equals(object& obj);
    dictionary clone();
    std::string toString();
    ~dictionary();
};

template<typename K, typename V>
dictionary<K, V>::dictionary() {  }

template<typename K, typename V>
dictionary<K, V>::dictionary(int s) {
    this->size = s;
    this->array = new K[s];
}

template<typename K, typename V>
void dictionary<K, V>::ensureCapacity() {
     if(SIZE == (sizeof(array) / sizeof(*array))) {
         int newsize = (sizeof(array) / sizeof(*array)) * 2;
         K *dest = new K[newsize];
         copy(array, array, dest);
     }
}

template<typename K, typename V>
void dictionary<K, V>::set(K elem, V val) {
    // for(int i=0; i<size; i++) {
    //     array[i] = val;
    // }
    for(int i=0; i<size; i++) {
        arr[elem] = val;
    }
}

template<typename K, typename V>
void dictionary<K, V>::get() {
    // for(int i=0; i<this->size; i++) {
    //     cout << i << " " << array[i] << " " << typeid(array[i]).name() << endl;
    // }
    print_map(arr);
}

template<typename K, typename V>
std::string dictionary<K, V>::getClass() {
    return "";
}

template<typename K, typename V>
bool dictionary<K, V>::equals(object &obj) {
    if (this == &obj) {
        return true;
    } else {
        return false;
    }
}

template<typename K, typename V>
dictionary<K, V> dictionary<K, V>::clone() {
    return *this;
}

template<typename K, typename V>
std::string dictionary<K, V>::toString() {
    return typeid(object).name();
}

template<typename K, typename V>
dictionary<K, V>::~dictionary() { }

#endif //LOTOS_DICTIONARY_H
