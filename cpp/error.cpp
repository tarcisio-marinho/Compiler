#include "error.h"


void Error::token_error(Scanner n, std::string lexema){
    std::string linha, coluna, lex, lexema;
    std::string error = std::string("ERRO na linha ") += std::to_string(n.n_linha) += std::string(", coluna ") 
                        += std::to_string(n.n_coluna) += std::string(", ultimo token lido ")  += lexema;

    std::cout << error << std::endl; 
    exit(-1);

}



void Error::sintaxe_error(){

}