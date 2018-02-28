#ifndef __TOKEN__
#define __TOKEN__

#include <string>
#include <iostream>
#include "gramatica.h"

class Token{
public:
    int codigo;
    std::string lexema;
    Gramatica g;
    Token(int cod, std::string lex);
};

#endif