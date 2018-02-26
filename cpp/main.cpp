#include "scanner.h"
#include <iostream>
#include <string>
#include "regular-exp.h"

void error(const std::string& message){
    std::cout << "Error: " << message << std::endl;
    exit(-1);
}

int main(int argc, char * argv[]){
    
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

        FILE *f = fopen(argv[1], "r");
        if(f == NULL){
            std::string file_name = std::string(argv[1]) += ": arquivo ou diretorio inexistente";
            error(file_name);
        
        }
        
    }

}