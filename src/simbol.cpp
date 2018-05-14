#include "simbol.h"


Simbol::Simbol(Token *t, int tipo, int escopo){
    this->t = t;
    this->tipo = tipo;
    this->escopo = escopo;
}