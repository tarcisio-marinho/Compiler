
#ifndef __REGEX__
#define __REGEX__

#include<string>
#include<regex>

class Reg{
public:

    std::regex letra = std::regex("[a-z]");
    std::regex caps = std::regex("[A-Z]");
    std::regex digito = std::regex("[0-9]");
    std::regex caracter = std::regex("([a-zA-Z]|[0-9]|_)");

    bool is_letra(std::string s);
    bool is_caps(std::string s);
    bool is_digito(std::string s);
    bool is_caracter(std::string s);
};


#endif