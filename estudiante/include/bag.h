#ifndef __BAG_H__
#define __BAG_H__

/**
 *  \brief TDA abstracto Bolsa
 *
 *  Este TDA abstracto nos permite trabajar con una colección de elementos que
 *  permite la extracción de elementos de forma aleatoria sin reemplazamiento
 */


#include<iostream>
#include<string>
#include <stdlib.h>
#include <vector>
#include <time.h>

using namespace std;

template <class T>

class Bag {

private:
    vector<T> v;

public:
    Bag(){

    }

    void add(const T element){
        v.push_back(element);
    }

    T get(){

        if(!v.empty()) {
            srand(time(NULL));
            int num = rand() % v.size();
            T uno;
            uno = v[num];

            v[num] = v.back();
            v.pop_back();


            return uno;
        }
    }

    void clear(){
        v.clear();
    }

    unsigned int size() const{
        return v.size();
    }

    bool empty(){
        return v.empty();
    }

    const Bag<T>&operator=(const Bag<T>& other){


        if(this !=&other)
            (*this).v = other.v;

        return *this;
    }
};
#endif
