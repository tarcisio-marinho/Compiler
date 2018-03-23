#include "parser.h"

/*
    <decl_var> ::= <tipo> <id> {,<id>}* ";"
    
    <tipo> ::= int | float | char
    
    <programa> ::= int main"("")" <bloco>
    
    <bloco> ::= “{“ {<decl_var>}* {<comando>}* “}”
    
    <comando> ::= <comando_básico> | <iteração> | if "("<expr_relacional>")" <comando> {else <comando>}?
    
    <comando_básico> ::= <atribuição> | <bloco>
    
    <iteração> ::= while "("<expr_relacional>")" <comando> | do <comando> while "("<expr_relacional>")"";"
    
    <atribuição> ::= <id> "=" <expr_arit> ";"
    
    <expr_relacional> ::= <expr_arit> <op_relacional> <expr_arit>
    
    <expr_arit> ::= <expr_arit> "+" <termo>   | <expr_arit> "-" <termo> | <termo>
    
    <termo> ::= <termo> "*" <fator> | <termo> “/” <fator> | <fator>
    
    <fator> ::= “(“ <expr_arit> “)” | <id> | <real> | <inteiro> | <char>

*/

void Parser::next_token(){
    this->look_ahead = this->scanner->scan();
}


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
    
    if(look_ahead->identificador != Gramatica::FECHACHAVE){
        Error::token_esperado_nao_encontrado(look_ahead, "}");
    }
    
}


/*
    <comando> ::= <comando_básico> | <iteração> | if "("<expr_relacional>")" <comando> {else <comando>}?
*/
void Parser::comando(){
    if(is_comando_basico){
        comando_basico();
    }
    else if(is_iteracao()){
        iteracao();
    }
    else if(look_ahead->identificador == Gramatica::IF){
        
    }else{
        Error::token_esperado_nao_encontrado(look_ahead, "if | identificador | { | while | do  ");
    }
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


void Parser::comando_basico(){


}


void Parser::iteracao(){


}





// IS's

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


bool Parser::is_comando_basico(){
    if(look_ahead->identificador == Gramatica::ID ||
       look_ahead->identificador == Gramatica::ABRECHAVE)
        return true;
    return false;
}


bool Parser::is_iteracao(){
    if(look_ahead->identificador == Gramatica::WHILE ||
        look_ahead->identificador == Gramatica::DO)
        return true;
    return false;
}
