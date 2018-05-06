#include "simbol.h"


Simbol::Simbol(std::string lexema, int tipo, int escopo){
    this->lexema = lexema;
    this->tipo = tipo;
    this->escopo = escopo;
}