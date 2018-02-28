#ifndef __TOKEN__
#define __TOKEN__

#include <string>
#include <iostream>
#include "gramatica.h"

class Token{
public:
    std::string lexema;
    int identificador;
    Token(int valor, std::string lex);
};

#endif