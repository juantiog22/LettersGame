#ifndef __LETTERS_BAG_H__
#define __LETTERS_BAG_H__

#include<map>
#include<iostream>
#include<string>
#include "letters_set.h"
#include <vector>
#include "bag.h"

/**
 * @brief TDA LettersBag
 *
 * Este TDA almacena un conjunto de chars utilizado en el juego de letras.
 * La estructura de datos subyacente es una lista de chars.
 */
class LettersBag {
private:
    Bag <char> letters;
public:

    LettersBag();

    LettersBag(const LettersSet & letterSet);

    void insertLetter(const char &I);

    char extractLetter();

    vector<char> extractLetters(int num);

    void clear();

    unsigned int size() const;

    LettersBag &operator=(const LettersBag &other);
};

#endif
