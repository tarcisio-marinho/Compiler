#ifndef __SCANNER__
#define __SCANNER__

#include "error.h"
#include "token.h"
#include "gramatica.h"
#include "regular-exp.h"
#include <iostream>

class Scanner{
public:

    Gramatica gramatica;
    Scanner(FILE *arq);
    Token scan();

    
private:
    FILE * arquivo;
    int n_linha, n_coluna;
    char caracter_lido; 

    void proximo_caracter();
    void incremento_l_c();

};


#endif