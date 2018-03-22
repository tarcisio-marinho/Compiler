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
    void parse();
    void next_token();
};

#endif
