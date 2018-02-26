
#ifndef __REGEX__
#define __REGEX__

#include<string>
#include<regex>

class Reg{
public:

    std::regex letra = std::regex("[a-z]");
    std::regex digito = std::regex("[0-9]");
    std::regex inteiro = std::regex("[0-9]+");
    std::regex ponto_flutuante = std::regex("[0-9]*.[0-9]+");
    std::regex caracter = std::regex("([a-z]|[0-9])");
    std::regex identificador = std::regex("(_|[a-z])(_|[a-z]|[0-9])*");

    bool is_letra(std::string s);
    bool is_digito(std::string s);
    bool is_caracter(std::string s);
    bool is_ponto_flutuante(std::string s);
    bool is_identificador(std::string s);
    bool is_inteiro(std::string s);
};


#endif