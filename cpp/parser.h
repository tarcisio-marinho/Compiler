#ifndef __PARSER__
#define __PARSER__

#include <iostream>
#include "error.h"
#include "scanner.h"
#include "token.h"
#include "gramatica.h"
#include "expressao.h"
#include "simbol.h"
#include <vector>
#include <stack>

class Parser{
public:
    FILE * arquivo;
    Scanner *scanner;
    Token * look_ahead;
    std::stack<Simbol*> simbol_table;
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
    Expressao* expressao_aritmetica();
    void expressao_aritmetica_recursiva();
    Expressao* termo();
    Expressao* fator();
    int tipo();

    bool is_declaracao_de_variavel();
    bool is_comando();
    bool is_comando_basico();
    bool is_iteracao();
    bool is_bloco();
    bool is_atribuicao();

    void new_simbol(Simbol * s);
    Simbol *search_simbol(std::string lexema, int escopo);
    void clean_simbols(int escopo);
    void Parser::check_types_expressao_relacional(Simbol * s1, Simbol *s2, int type1, int type2);

};

#endif
