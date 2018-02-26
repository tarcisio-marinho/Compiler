#include "error.h"


void Error::token_error(){
    std::string linha, coluna, lex, lexema;
    std::string error = std::string("ERRO na linha ") += linha += ", coluna " += coluna += ", ultimo token lido "  += lexema;
    std::cout << "Erro na linha: " << std::endl; 
    exit(-1);

}


void Error::sintaxe_error(){

}