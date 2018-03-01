#include "regular-exp.h"

bool Reg::is_letra(char c){
    std::string s;
    std::regex letra = std::regex("[a-z]");
    s.push_back(c);
    if(std::regex_match(s, letra))
        return true;
    return false;
}


bool Reg::is_caps(char c){
    std::string s;
    std::regex caps = std::regex("[A-Z]");
    s.push_back(c);
    if(std::regex_match(s, caps))
        return true;
    return false;
}


bool Reg::is_digito(char c){
    std::string s;
    std::regex digito = std::regex("[0-9]");
    s.push_back(c);
    if(std::regex_match(s, digito))
        return true;
    return false;
}


bool Reg::is_caracter(char c){
    std::string s;
    std::regex caracter = std::regex("([a-zA-Z]|[0-9]|_)");
    s.push_back(c);
    if(std::regex_match(s, caracter))
        return true;
    return false;
}
