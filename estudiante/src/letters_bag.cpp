//
// Created by jdrgj on 20/12/2022.
//
#include "letters_bag.h"
#include "letters_set.h"
#include <vector>
#include "bag.h"

using namespace std;



LettersBag::LettersBag() {


}

LettersBag::LettersBag(const LettersSet &letterSet) {

    map<char, LetterInfo> letras = letterSet.getLetters();
    for(std::map<char,LetterInfo>::const_iterator it=letras.begin(); it!=letras.end(); ++it){
        char letra = it->first;
        int rep = it->second.repetitions;
        while(rep != 0) {
            letters.add(letra);
            rep--;
        }
    }
}

void LettersBag::insertLetter(const char &I) {
    letters.add(I);
}

char LettersBag::extractLetter() {
    char x = letters.get();
    return x;
}

vector<char> LettersBag::extractLetters(int num) {
    vector<char> hola;
    for(int i=0;i<num;i++){
        hola.push_back(letters.get());
    }
    return hola;
}

void LettersBag::clear() {
    letters.clear();
}

unsigned int LettersBag::size() const {
    return letters.size();
}

LettersBag &LettersBag::operator=(const LettersBag &other) {

    if(this != &other) {
        letters = other.letters;
    }
    return *this;
}