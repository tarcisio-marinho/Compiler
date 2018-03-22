#include "parser.h"

Parser::Parser(FILE *f){
    this->arquivo = f;
    this->scanner = new Scanner(arquivo);
}

void Parser::parse(){
    next_token();
    if(look_ahead->identificador != Gramatica::INT){
        Error::token_esperado_nao_encontrado(look_ahead, "int");
    }

    next_token();
    if(look_ahead->identificador != Gramatica::MAIN){
        Error::token_esperado_nao_encontrado(look_ahead, "main");
    }
    
    next_token();
    if(look_ahead->identificador != Gramatica::ABREPARENTESES){
        Error::token_esperado_nao_encontrado(look_ahead, "(");
    }

    next_token();
    if(look_ahead->identificador != Gramatica::FECHAPARENTESES){
        Error::token_esperado_nao_encontrado(look_ahead, ")");
    }

    // Entrou no main
    bloco();

}


/*
    <bloco> ::= “{“ {<decl_var>}* {<comando>}* “}”
*/
void Parser::bloco(){
    
    next_token();
    if(look_ahead->identificador != Gramatica::ABRECHAVE){
        Error::token_esperado_nao_encontrado(look_ahead, "{");
    }

    next_token();
    while(is_declaracao_de_variavel()){ // Múltiplas declarações de variaveis
        declaracao_de_variavel();
    }

    while(is_comando()){
        comando();
    }
    
    
}


/*
    <comando> ::= <comando_básico> | <iteração> | if "("<expr_relacional>")" <comando> {else <comando>}?
*/
void Parser::comando(){

}


void Parser::declaracao_de_variavel(){
    std::string parte_do_erro = "Declaração de variável";
    // checagem de tipos ??
    next_token();
    if(look_ahead->identificador != Gramatica::ID){
        Error::token_esperado_nao_encontrado(look_ahead, std::string("Identificador"));
    }

    next_token();
    while(look_ahead->identificador == Gramatica::VIRGULA){
        
        next_token();
        if(look_ahead->identificador != Gramatica::ID){
            Error::token_esperado_nao_encontrado(look_ahead, std::string("Identificador"));
        }

        next_token();
    }

    if(look_ahead->identificador != Gramatica::PONTOVIRGULA){
        Error::token_esperado_nao_encontrado(look_ahead, std::string(";"));
    }

    next_token();
    
}


bool Parser::is_declaracao_de_variavel(){
    if (look_ahead->identificador == Gramatica::INT ||
        look_ahead->identificador == Gramatica::FLOAT ||
        look_ahead->identificador == Gramatica::CHAR)   
        return true;

    return false;
}


bool Parser::is_comando(){
    if(look_ahead->identificador == Gramatica::DO ||
        look_ahead->identificador == Gramatica::WHILE||
        look_ahead->identificador == Gramatica::ID ||
        look_ahead->identificador == Gramatica::IF ||
        look_ahead->identificador == Gramatica::ABRECHAVE)
        return true;
    return false;
}


void Parser::next_token(){
    this->look_ahead = this->scanner->scan();
}
