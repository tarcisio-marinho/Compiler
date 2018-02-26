#include "scanner.h"
#include <iostream>
#include <string>
#include <regex>

void error(const std::string& message){
    std::cout << "Error: " << message << std::endl;
    exit(-1);
}

int main(int argc, char * argv[]){
    std::string a = "eaemnkkk";
    std::regex letra = std::regex("[a-z]+");
    if(std::regex_match(a, letra))
        std::cout << "matchs";
    
    
    
    
    
    // if(argc < 2){
    //     std::string program_name = std::string(argv[0]) += ": no input files\ncompilation terminated.";
    //     error(program_name);

    // }else{
    //     FILE *f = fopen(argv[1], "r");
    //     if(f == NULL){
    //         std::string file_name = std::string(argv[1]) += ": no such file or directory";
    //         error(file_name);
        
    //     }
        
    // }
}