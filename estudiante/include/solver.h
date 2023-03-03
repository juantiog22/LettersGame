//
// Created by jdrgj on 27/12/2022.
//

#ifndef P04_JUEGO_LETRAS_SOLVER_H
#define P04_JUEGO_LETRAS_SOLVER_H


#include <iostream>
#include <fstream>
#include "dictionary.h"
#include "letters_set.h"
#include <vector>
#include <map>

class Solver{

private:
    Dictionary diccionario;
    LettersSet letras;

public:
    Solver(const Dictionary & dict, const LettersSet & letters_set);

    //pair <vector<string>,int> getSolutions(const vector <char> & avaible_letters, bool score_game);
};


#endif //P04_JUEGO_LETRAS_SOLVER_H
