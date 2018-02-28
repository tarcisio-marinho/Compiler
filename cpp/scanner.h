#ifndef __SCANNER__
#define __SCANNER__

#include "error.h"
#include "token.h"
#include "gramatica.h"
#include "regular-exp.h"
#include <ctype>
#include <iostream>

class Scanner{
public:
    int n_linha, n_coluna;
    char caracter_lido; 
    FILE * arquivo;
    Gramatica gramatica;
    Reg regular_expression;

    Scanner(FILE *arq);
    Token scan();
    void proximo_caracter();
    void incremento_l_c();
};


#endif