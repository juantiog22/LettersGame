//
// Created by jdrgj on 20/12/2022.
//

#include "letters_set.h"
#include<map>

using namespace std;



LettersSet::LettersSet() {}


LettersSet::LettersSet(const LettersSet & other) {
    letters = other.letters;
}

bool LettersSet::insert(const pair<char, LetterInfo> & val ){
    bool correct = false;
    if(letters.find(val.first) == letters.end()){
        correct=true;
    }
    if(correct)
        letters.insert(val);

    return correct;
}

bool LettersSet::find(char clave){
    bool correct = false;
    if(letters.find(clave) != letters.end()) {
        correct = true;
    }
    return correct;
}

bool LettersSet::erase(const char &key){
    return letters.erase(key);
}

void LettersSet::clear() {
    letters.clear();
}

bool LettersSet::empty() const {
    return letters.empty();
}

int LettersSet::size() const {
    return letters.size();
}

int LettersSet::getScore(string word) {
    int total=0;
    for(int i=0; i<word.length(); i++){
        total += letters[toupper(word[i])].score;
    }
    return total;
}

map<char,LetterInfo> LettersSet::getLetters() const{
    return letters;
}


LettersSet & LettersSet::operator=(const LettersSet & cl){
    this->letters = cl.letters;
    return *this;
}

LetterInfo & LettersSet::operator[](const char & val){
    return letters[val];
}


ostream& operator<<(ostream& os, const LettersSet & cl){
    os << "Letra    Cantidad    Puntos" <<endl;
    for(std::map<char,LetterInfo>::const_iterator it=cl.letters.begin(); it!=cl.letters.end(); ++it){
        os << it->first << "    "  << it->second.repetitions << "   " << it->second.score <<endl;
    }
    return os;
}

istream& operator>>(istream& is, LettersSet & cl){
    string cabecera;
    is >> cabecera >> cabecera >> cabecera;
    while(is) {
        LetterInfo info;
        char letra;
        is >> letra >> info.repetitions >> info.score;
        std::pair<char, LetterInfo> letters_aux;
        letters_aux.first = letra;
        letters_aux.second = info;
        cl.insert(letters_aux);
    }
}
