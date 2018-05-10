#ifndef SIMBOL_H
#define SIMBOL_H
#include <string>
#include <iostream>
#include "token.h"

class Simbol{
public:
    Token *t;
    int tipo;
    int escopo;
    Simbol(Token *t, int tipo, int escopo);
};

#endif