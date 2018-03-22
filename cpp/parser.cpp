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
    Bloco -> Declaração de variaveis | comando
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

}


void Parser::declaracao_de_variavel(){
    
}


bool Parser::is_declaracao_de_variavel(){
    if (look_ahead->identificador == Gramatica::INT ||
        look_ahead->identificador == Gramatica::FLOAT ||
        look_ahead->identificador == Gramatica::CHAR)   
        return true;

    return false;
}

void Parser::next_token(){
    this->look_ahead = this->scanner->scan();
}
