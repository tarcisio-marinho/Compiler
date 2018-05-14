#include "expressao.h"

Expressao::Expressao(int tipo, std::string l){
    this->lexema = l;
    this->tipo = tipo;
}


Expressao::Expressao(int tipo){
    this->tipo = tipo;
}


Expressao::Expressao(std::string s){
    this->lexema = s;
}