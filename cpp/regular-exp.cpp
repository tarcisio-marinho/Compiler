#include "regular-exp.h"

bool Reg::is_letra(std::string s){
    if(std::regex_match(s, letra))
        return true;
    return false;
}


bool Reg::is_digito(std::string s){
    if(std::regex_match(s, digito))
        return true;
    return false;
}


bool Reg::is_caracter(std::string s){
    if(std::regex_match(s, caracter))
        return true;
    return false;
}


bool Reg::is_ponto_flutuante(std::string s){
    if(std::regex_match(s, ponto_flutuante))
        return true;
    return false;
}


bool Reg::is_identificador(std::string s){
    if(std::regex_match(s, identificador))
        return true;
    return false;
}


bool Reg::is_inteiro(std::string s){
    if(std::regex_match(s, inteiro))
        return true;
    return false;
}

