#ifndef SIMBOL_H
#define SIMBOL_H
#include <string>
#include <iostream>
#include "token.h"
#include <string>

class Simbol{
public:
    Token *t;
    int tipo;
    int escopo;
    std::string lexema;
    Simbol(std::string l, int tipo, int escopo, Token *t);
};

#endif