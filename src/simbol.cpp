#include "simbol.h"


Simbol::Simbol(std::string l, int tipo, int escopo, Token *t){
    this->t = t;
    this->tipo = tipo;
    this->escopo = escopo;
    this->lexema = l;
}