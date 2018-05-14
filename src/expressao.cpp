#include "expressao.h"

Expressao::Expressao(std::string l, int tipo){
    this->lexema = l;
    this->tipo = tipo;
}


Expressao::Expressao(int tipo){
    this->tipo = tipo;
}


Expressao::Expressao(std::string s){
    this->lexema = s;
}