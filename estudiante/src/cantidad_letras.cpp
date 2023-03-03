//
// Created by jdrgj on 27/12/2022.
//
#include<iostream>
#include "dictionary.h"
#include <fstream>
#include "letters_set.h"


int main(int argc, char *argv[])
{
    if(argc != 3){
        cout << "Los parametros son: " << endl;
        cout << "1.- El fichero con el diccionario" << endl;
        cout << "2.- El fichero con el LettersSet" << endl;
        return 1;
    }

    Dictionary diccionario;
    LettersSet letras;

    ifstream fi, fi2;
    if (!fi or !fi2) {       //Si algún fuchero no puede abrirse muestra mensaje error y se sale del programa
        cout << "Error al abrir el ejemplo" << endl;
        exit(EXIT_FAILURE);
    }
    fi.open(argv[1]);                   //Abrimos fichero 1
    fi2.open(argv[2]);                  //Abrimos fichero 2

    fi >> diccionario;                 //Guardamos contenido fi en diccionario
    fi2 >> letras;                      //Guardamos contenido fi2 en letras

    cout << "Letra\tUsos\tOcurrencias" << endl;
    int totalUsages=0;
    int totalOcurrences=0;

    for (LettersSet::iterator it = letras.begin(); it != letras.end(); ++it) {

        totalUsages = diccionario.getTotalUsages((*it).first);
        totalOcurrences = diccionario.getOccurrences((*it).first);

        cout << (*it).first << "\t" << totalUsages << "\t" << totalOcurrences << endl;
    }

    return 0;
}
