#ifndef EXPRESSAO
#define EXPRESSAO
#include <iostream>
#include <string>
class Expressao{
public:
    int tipo, op;
    std::string lexema;
    Expressao(int tipo, std::string l);
    Expressao(int tipo);
    Expressao(std::string s);
};

#endif