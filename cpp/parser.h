#ifndef __PARSER__
#define __PARSER__

#include<iostream>
#include "error.h"
#include "scanner.h"
#include "token.h"
#include "gramatica.h"

class Parser{
public:
    FILE * arquivo;
    Scanner *scanner;
    Token * look_ahead;

    Parser(FILE *f);
    void next_token();
    void parse();
    void bloco();
    void comando();
    void declaracao_de_variavel();
    void comando_basico();
    void expressao_relacional();
    void iteracao();
    void atribuicao();

    bool is_declaracao_de_variavel();
    bool is_comando();
    bool is_comando_basico();
    bool is_iteracao();
    bool is_bloco();
    bool is_atribuicao();
};

#endif
