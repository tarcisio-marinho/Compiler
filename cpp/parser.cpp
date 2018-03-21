#include "parser.h"

Parser::Parser(FILE *f){
    arquivo = f;
    scanner = new Scanner(arquivo);
}

void Parser::parse(){
    
    while(true){
        Token td = scanner->scan();
        std::cout << "token lido: " << td.lexema << " identificador: " << td.identificador << std::endl;
        
        if(td.lexema == "EOF"){
            break;
        }
    }
}
