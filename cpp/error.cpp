#include "error.h"

//BLUE, RED, WHITE, YELLOW, MAGENTA, GREEN, END = '\33[94m', '\033[91m', '\33[97m', '\33[93m', '\033[1;35m', '\033[1;32m', '\033[0m'

// Léxico

void Error::float_error(int linha, int coluna, std::string lexema){
    std::string error = std::string("\033[91mERRO\033[0m: na linha: \33[93m") += std::to_string(linha) += std::string("\033[0m, coluna: \33[93m") 
                        += std::to_string(coluna) += std::string("\033[0m, ultimo token lido: \033[1;32m")  += lexema 
                        += std::string("\033[0m, float mal formado");

    std::cout << error << std::endl; 
    exit(-1);    
}


void Error::char_error(int linha, int coluna, std::string lexema){
    std::string error = std::string("\033[91mERRO\033[0m: na linha: \33[93m") += std::to_string(linha) += std::string("\033[0m, coluna: \33[93m") 
                        += std::to_string(coluna) += std::string("\033[0m, ultimo token lido: \033[1;32m")  += lexema 
                        += std::string("\033[0m, char mal formado");

    std::cout << error << std::endl; 
    exit(-1);    
}


void Error::comentario_error(int linha, int coluna, std::string lexema){
    std::string error = std::string("\033[91mERRO\033[0m: na linha: \33[93m") += std::to_string(linha) += std::string("\033[0m, coluna: \33[93m") 
                        += std::to_string(coluna) += std::string("\033[0m, ultimo token lido: \033[1;32m")  += lexema 
                        += std::string("\033[0m, comentario não fechado");

    std::cout << error << std::endl; 
    exit(-1);    
}


void Error::caracter_invalido_error(int linha, int coluna, std::string lexema){
    std::string error = std::string("\033[91mERRO\033[0m: na linha: \33[93m") += std::to_string(linha) += std::string("\033[0m, coluna: \33[93m") 
                        += std::to_string(coluna) += std::string("\033[0m, ultimo token lido: \033[1;32m")  += lexema 
                        += std::string("\033[0m, caracter inválido");

    std::cout << error << std::endl; 
    exit(-1);    
}


void Error::diferenca_error(int linha, int coluna, std::string lexema){
    std::string error = std::string("\033[91mERRO\033[0m: na linha: \33[93m") += std::to_string(linha) += std::string("\033[0m, coluna: \33[93m") 
                        += std::to_string(coluna) += std::string("\033[0m, ultimo token lido: \033[1;32m")  += lexema 
                        += std::string("\033[0m, diferença mal formada");

    std::cout << error << std::endl; 
    exit(-1);    
}


// Sintático

void Error::token_esperado_nao_encontrado(Token *t, std::string esperado){
    std::string error = std::string("\033[91mERRO\033[0m: na linha: \33[93m") += std::to_string(t->linha) += std::string("\033[0m, coluna: \33[93m") 
                        += std::to_string(t->coluna) += std::string("\033[0m. Token esperado: \033[1;32m")  += esperado 
                        += std::string("\033[0m Token lido: \033[1;32m") += t->lexema += std::string("\033[0m");

    std::cout << error << std::endl; 
    exit(-1); 
}
