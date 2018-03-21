#include "parser.h"

Parser::Parser(FILE *f){
    this->arquivo = f;
    this->scanner = new Scanner(arquivo);
}

void Parser::parse(){

    while(true){
        next_token();

        std::cout << "token lido: " << this->look_ahead->lexema << " identificador: " << this->look_ahead->identificador << std::endl;
        
        if(this->look_ahead->lexema == "EOF"){
            break;
        }
    }
}

void Parser::next_token(){
    this->look_ahead = this->scanner->scan();
}
