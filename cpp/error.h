#ifndef __ERROR__
#define __ERROR__

#include "scanner.h"
#include <iostream>
#include <string>

class Error{
public:
    static void float_error(int linha, int coluna, std::string lexema);
    static void char_error(int linha, int coluna, std::string lexema);
    static void comentario_error(int linha, int coluna, std::string lexema);
    static void caracter_invalido_error(int linha, int coluna, std::string lexema);
    static void diferenca_error(int linha, int coluna, std::string lexema);
};



#endif