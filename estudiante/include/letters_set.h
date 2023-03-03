#ifndef __LETTER_SET_H__
#define __LETTER_SET_H__

#include<map>
#include<iostream>
#include<string>


using namespace std;

/**
 * @brief TDA LetterInfo
 *
 * Contiene información sobre un determinado carácter del juego de las
 * letras. En concreto, almacena información sobre el número de repeticiones de
 * la letra en la partida y de la puntuación que otorga al utilizarse en una
 * palabra
 */

struct LetterInfo{
    int repetitions;
    int score;

};




/**
 * @brief TDA LettersSet
 *
 * Este TDA representa un conjunto de letras, con la información necesaria para
 * jugar una partida al juego de las letras, es decir, el número de repeticiones
 * que tenemos de la letra y la puntuación que dicha letra otorga cuando se
 * utiliza en una palabra
 */


class LettersSet{

private:
    map<char, LetterInfo> letters;

public:

    LettersSet();

    LettersSet(const LettersSet &other);

    bool insert(const pair<char, LetterInfo> & val );

    bool find(char clave);

    bool erase(const char &key);

    void clear();

    bool empty() const;

    int size() const;

    int getScore(string word);

    map<char,LetterInfo> getLetters() const;

    LettersSet & operator=(const LettersSet & cl);

    LetterInfo & operator[](const char & val);

    friend ostream& operator<<(ostream& os, const LettersSet & cl);

    friend istream& operator>>(istream& is, LettersSet & cl);

    class iterator{

    private:
        map<char,LetterInfo>::iterator it;

    public:


        iterator(){};

        iterator(const map<char,LetterInfo>::iterator iter){
            it = iter;
        }


        iterator &operator=(const map<char,LetterInfo>::iterator &iter){
            it=iter;
            return (*this);
        }

        const pair<char,LetterInfo> operator *() const{
            return *it;
        }

        iterator &operator++(){
            ++it;
            return (*this);
        }

        iterator &operator--(){
            --it;
            return (*this);
        }

        bool operator ==(const iterator &other){
            return it == other.it;
        }

        bool operator !=(const iterator &other){
            return it != other.it;
        }

    };


    iterator begin(){
        iterator it;
        it = this->letters.begin();
        return it;
    }

    iterator end(){
        iterator it;
        it = this->letters.end();
        return it;
    }

};

#endif
