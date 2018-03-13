#include "scanner.h"
#include <iostream>
#include <string>
#include "token.h"
#include "regular-exp.h"

//BLUE, RED, WHITE, YELLOW, MAGENTA, GREEN, END = '\33[94m', '\033[91m', '\33[97m', '\33[93m', '\033[1;35m', '\033[1;32m', '\033[0m'

void error(const std::string& message){
    std::cout << "\033[91mError\33[97m: " << message << std::endl;
    exit(-1);
}

int main(int argc, char * argv[]){
    FILE *f;
    
    if(argc < 2){
        std::string program_name = std::string(argv[0]) += ": arquivo não especificado\nCompilação terminada.";
        error(program_name);

    }else{
        
        if(std::string(argv[1]) == "-h" || std::string(argv[1]) == "--help"){
            std::string help = std::string("Compilador C\nUSO:\n");   
            std::string program_name = std::string(argv[0]);
            help += program_name += " <path/file>";

            std::cout << help << std::endl;
            return 0; 
        }

        f = fopen(argv[1], "r");
        if(f == NULL){
            std::string file_name = std::string(argv[1]) += ": arquivo ou diretorio inexistente";
            error(file_name);
        
        }

        Scanner s(f);
        
        while(true){
            Token td = s.scan();
            std::cout << td.lexema << std::endl;
            
            if(td.lexema == "EOF"){
                break;
            }
        }
    }
}