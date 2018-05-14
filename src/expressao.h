#ifndef EXPRESSAO
#define EXPRESSAO
#include <iostream>
#include <string>
class Expressao{
public:
    int tipo, op;
    std::string lexema;
    Expressao(std::string l, int tipo);
};

#endif