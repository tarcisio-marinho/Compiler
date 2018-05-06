#ifndef __PARSER__
#define __PARSER__

#include <iostream>
#include "error.h"
#include "scanner.h"
#include "token.h"
#include "gramatica.h"
#include "simbol.h"
#include <vector>
class Parser{
public:
    FILE * arquivo;
    Scanner *scanner;
    Token * look_ahead;
    std::vector<Simbol> simbol_table;
    int escopo;

    Parser(FILE *f);
    void next_token();
    void parse();
    void bloco();
    void comando();
    void comando_if();
    void comando_while();
    void comando_do();
    void expressao_relacional();
    void operador_relacional();
    void declaracao_de_variavel();
    void comando_basico();
    void iteracao();
    void atribuicao();
    void expressao_aritmetica();
    void expressao_aritmetica_recursiva();
    void termo();
    void fator();

    bool is_declaracao_de_variavel();
    bool is_comando();
    bool is_comando_basico();
    bool is_iteracao();
    bool is_bloco();
    bool is_atribuicao();
};

#endif
