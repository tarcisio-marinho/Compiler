#ifndef __PARSER__
#define __PARSER__

#include <iostream>
#include "error.h"
#include "scanner.h"
#include "token.h"
#include "gramatica.h"
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
    int cont;
    int label;
    int cont_if, cont_while, cont_do_while; 

    Parser(FILE *f);
    void next_token();
    void parse();
    void bloco();
    void comando();
    void comando_if();
    void comando_while();
    void comando_do();
    std::string expressao_relacional();
    int operador_relacional();
    void declaracao_de_variavel();
    void comando_basico();
    void iteracao();
    void atribuicao();
    Simbol* expressao_aritmetica();
    Simbol* expressao_aritmetica_recursiva();
    Simbol* termo();
    Simbol* fator();
    int tipo();

    bool is_declaracao_de_variavel();
    bool is_comando();
    bool is_comando_basico();
    bool is_iteracao();
    bool is_bloco();
    bool is_atribuicao();


    // Sematico
    void new_simbol(Simbol * s);
    Simbol *search_simbol(std::string lexema);
    bool search_simbol_in_scope(std::string lexema, int escopo);
    void clean_simbols(int escopo);
    void check_types_expressao_relacional(Token *s, int type1, int type2);
    void check_types_atribuicao(Token *s, int type1, int type2);
    int check_types_termo(Simbol* e1, Simbol* e2, int op, Token *s);
    int check_types_expressao_aritmetica(int tipo1, int tipo2, Token *t);

    // Gerador codigo intermediario
    void print_codigo_intermediario(std::string s);
};

#endif
