#include "token.h"

Token::Token(int valor, std::string lex, int l, int c){
    lexema = lex;
    identificador = valor;
    linha = l;
    coluna = c;
}
