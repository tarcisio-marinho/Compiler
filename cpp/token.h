#ifndef __TOKEN__
#define __TOKEN__

#include<string>
#include<iostream>

class Token{
public:
    int codigo;
    std::string lexema;
    Token(int cod, std::string lex);
};

#endif