#ifndef __PARSER__
#define __PARSER__

#include<iostream>
#include "error.h"
#include "scanner.h"
#include "token.h"

class Parser{
public:
    FILE * arquivo;
    Scanner *scanner;

    Parser(FILE *f);
    void parse();
};




#endif