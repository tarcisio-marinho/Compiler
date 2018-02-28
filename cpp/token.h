#ifndef __TOKEN__
#define __TOKEN__

#include <string>
#include <iostream>
#include "gramatica.h"

class Token{
public:
    std::string lexema;
    int identificador;
    Token(Gramatica g, std::string lex);
};

#endif