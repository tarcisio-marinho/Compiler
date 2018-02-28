#include "token.h"

Token::Token(Gramatica g, std::string lex){
    lexema = lex;
    gramatica = g;
}