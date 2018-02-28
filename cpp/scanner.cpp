#include "scanner.h"

Scanner::Scanner(FILE * arq){
    n_linha = 1;
    n_coluna = 0;
    caracter_lido = ' ';
    arquivo = arq;
}


Token Scanner::scan(){
    std::string lexema;
    
  
    while(true){
        
        while(isspace(caracter_lido)){
            proximo_caracter();
        }
        
        if(caracter_lido == EOF){
            return Token(gramatica.EoF, std::string("EOF"));
        }

        else if(regular_expression.)



        
        

        
        
    }
    return Token(gramatica.ID, std::string("eaemen kk"));

    
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