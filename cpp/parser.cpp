#include "parser.h"

Parser::Parser(FILE *f){
    arquivo = f;
    //scanner(arquivo);
}

void Parser::parse(){
    Scanner s(arquivo);
        
    while(true){
        Token td = s.scan();
        std::cout << "token lido: " << td.lexema << " identificador: " << td.identificador << std::endl;
        
        if(td.lexema == "EOF"){
            break;
        }
    }
}
