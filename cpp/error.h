#ifndef __ERROR__
#define __ERROR__

#include "scanner.h"
#include<iostream>
#include<string>

class Error{
public:
    static void token_error(Scanner n, std::string lexema);
    static void sintaxe_error();
};



#endif