
#ifndef __REGEX__
#define __REGEX__

#include<string>
#include<regex>

class Reg{
public:
    static bool is_letra(char c);
    static bool is_caps(char c);
    static bool is_digito(char c);
    static bool is_caracter(char c);
};


#endif