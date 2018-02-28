#ifndef __SCANNER__
#define __SCANNER__

#include "error.h"
#include "token.h"
#include "gramatica.h"
#include <iostream>

class Scanner{
public:
    int n_linha, n_coluna;
    char caracter_lido; 
    FILE * arquivo;


    Scanner(FILE *arq);
    Token scan();
    void proximo_caracter();
    void incremento_l_c();
};


#endif