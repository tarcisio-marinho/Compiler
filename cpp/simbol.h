#ifndef SIMBOL_H
#define SIMBOL_H
#include <string>
#include <iostream>

class Simbol{
public:
    std::string lexema;
    int tipo;
    int escopo;
    Simbol(std::string lexema, int tipo, int escopo);
};

#endif