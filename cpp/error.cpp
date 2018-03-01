#include "error.h"

void Error::float_error(int linha, int coluna, std::string lexema){
    std::string error = std::string("ERRO: na linha: ") += std::to_string(linha) += std::string(", coluna: ") 
                        += std::to_string(coluna) += std::string(", ultimo token lido: ")  += lexema 
                        += std::string(", float mal formado");

    std::cout << error << std::endl; 
    exit(-1);    
}


void Error::char_error(int linha, int coluna, std::string lexema){
    std::string error = std::string("ERRO: na linha: ") += std::to_string(linha) += std::string(", coluna: ") 
                        += std::to_string(coluna) += std::string(", ultimo token lido: ")  += lexema 
                        += std::string(", char mal formado");

    std::cout << error << std::endl; 
    exit(-1);    
}


void Error::comentario_error(int linha, int coluna, std::string lexema){
    std::string error = std::string("ERRO: na linha: ") += std::to_string(linha) += std::string(", coluna: ") 
                        += std::to_string(coluna) += std::string(", ultimo token lido: ")  += lexema 
                        += std::string(", comentario não fechado");

    std::cout << error << std::endl; 
    exit(-1);    
}


void Error::caracter_invalido_error(int linha, int coluna, std::string lexema){
    std::string error = std::string("ERRO: na linha: ") += std::to_string(linha) += std::string(", coluna: ") 
                        += std::to_string(coluna) += std::string(", ultimo token lido: ")  += lexema 
                        += std::string(", caracter inválido");

    std::cout << error << std::endl; 
    exit(-1);    
}


void Error::diferenca_error(int linha, int coluna, std::string lexema){
    std::string error = std::string("ERRO: na linha: ") += std::to_string(linha) += std::string(", coluna: ") 
                        += std::to_string(coluna) += std::string(", ultimo token lido: ")  += lexema 
                        += std::string(", diferença mal formada");

    std::cout << error << std::endl; 
    exit(-1);    
}
