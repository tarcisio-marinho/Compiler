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

void Parser::next_token(){
    this->look_ahead = this->scanner->scan();
}
