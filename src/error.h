#ifndef __ERROR__
#define __ERROR__

#include "scanner.h"
#include "token.h"
#include <iostream>
#include <string>
#include "simbol.h"

class Error{
public:
    // Lexic
    static void float_error(int linha, int coluna, std::string lexema);
    static void char_error(int linha, int coluna, std::string lexema);
    static void comentario_error(int linha, int coluna, std::string lexema);
    static void caracter_invalido_error(int linha, int coluna, std::string lexema);
    static void diferenca_error(int linha, int coluna, std::string lexema);

    // Parser
    static void token_esperado_nao_encontrado(Token *t, std::string esperado, std::string funcao);

    // Semantic
    static void atribuicao_incompativel(Simbol *s, int tipo1, int tipo2);
    static void char_nao_opera_com_outros_tipos(Simbol *s, int tipo1, int tipo2);
    static void variavel_nao_declarada(Simbol *s);
    static void identificador_repetido(Simbol *s);
};



#endif