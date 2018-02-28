#include "scanner.h"

Scanner::Scanner(FILE * arq){
    n_linha = 1;
    n_coluna = 0;
    caracter_lido = ' ';
    arquivo = arq;
    Gramatica gra;

}


Token Scanner::scan(){
    std::string lexema;
    

    while(true){
        if(feof(arquivo)){
            std::cout << "EOF FIND" << std::endl;
            break;
        }

        proximo_caracter();
        std::cout << caracter_lido << std::endl;

        
    }
    
    return Token(gra.ID, "eaemen kk");

    std::cout << "CONSEGUI SAIR" << std::endl;
    // if(feof(arquivo)){
    //     std::cout << "saindo";
    // }
}


void Scanner::incremento_l_c(){
    
    if(caracter_lido == '\n'){ // new line
        n_coluna = 0; 
        n_linha +=1;

    }else if(caracter_lido == '\t'){
        n_coluna +=4; // tab
    
    }else{
        n_coluna +=1; // normal char
    }
}


void Scanner::proximo_caracter(){
    caracter_lido = (char)fgetc(arquivo);
    incremento_l_c();
}