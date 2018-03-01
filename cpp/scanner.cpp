#include "scanner.h"

Scanner::Scanner(FILE * arq){
    n_linha = 1;
    n_coluna = 0;
    caracter_lido = ' ';
    arquivo = arq;
}


Token Scanner::scan(){
    std::string lexema = "";
    
  
    while(true){
        
        while(isspace(caracter_lido)){
            proximo_caracter();
        }
        
        if(caracter_lido == EOF){
            return Token(gramatica.EoF, std::string("EOF"));
        }

        else if(Reg::is_letra(caracter_lido) || caracter_lido == '_'){
            while(Reg::is_caracter(caracter_lido) || caracter_lido == '_'){
                lexema.push_back(caracter_lido);
                proximo_caracter();
            }

            return Token(gramatica.ID, lexema);
        }

        else if(Reg::is_digito(caracter_lido)){
            lexema.push_back(caracter_lido);
            proximo_caracter();

            while(Reg::is_digito(caracter_lido)){
                lexema.push_back(caracter_lido);
                proximo_caracter();
            }

            if(caracter_lido == '.'){
                lexema.push_back(caracter_lido);
                proximo_caracter();

                if(!Reg::is_digito(caracter_lido)){
                    Error::float_error(n_linha, n_coluna, lexema);
                }

                while(Reg::is_digito(caracter_lido)){
                    lexema.push_back(caracter_lido);
                    proximo_caracter();
                }

                return Token(gramatica.TIPOFLOAT, lexema);
            }

            return Token(gramatica.TIPOINT, lexema);
        }

        else if(caracter_lido == '.'){
            lexema.push_back(caracter_lido);
            proximo_caracter();

            if(!Reg::is_digito(caracter_lido)){
                Error::float_error(n_linha, n_coluna, lexema);
            }

            while(Reg::is_digito(caracter_lido)){
                lexema.push_back(caracter_lido);
                proximo_caracter();
            }

            return Token(gramatica.TIPOFLOAT, lexema);
        }

        else if(caracter_lido == '\''){
            lexema.push_back(caracter_lido);
            proximo_caracter();

            if(!Reg::is_caracter(caracter_lido)){
                Error::char_error(n_linha, n_coluna, lexema);
            }

            lexema.push_back(caracter_lido);
            proximo_caracter();

            if(caracter_lido != '\''){
                Error::caracter_invalido_error(n_linha, n_coluna, lexema);
            }

            lexema.push_back(caracter_lido);
            proximo_caracter();

            return Token(gramatica.TIPOCHAR, lexema);
        }

        else if(caracter_lido == '+'){ // ++ += ?? 
            lexema.push_back(caracter_lido);
            proximo_caracter();
            return Token(gramatica.SOMA, lexema);
        }

        else if(caracter_lido == '-'){ // -- -= ??
            lexema.push_back(caracter_lido);
            proximo_caracter();
            return Token(gramatica.SUBTRACAO, lexema);
        }

        else if(caracter_lido == '*'){ // *=
            lexema.push_back(caracter_lido);
            proximo_caracter();
            return Token(gramatica.MULTIPLICACAO, lexema);
        }

        else if(caracter_lido == '/'){
            lexema.push_back(caracter_lido);
            proximo_caracter();

            if(caracter_lido == '/'){ // comentario de uma linha
                while(caracter_lido != '\n'){
                    lexema.push_back(caracter_lido);
                    proximo_caracter();
                }
            }
            else if(caracter_lido == '*'){ // comentario de multiplas linhas
                lexema.push_back(caracter_lido);
                proximo_caracter();

                while(true){
                    if(caracter_lido == '*'){
                        proximo_caracter();

                        if(caracter_lido == '/'){
                            proximo_caracter();
                            break;
                        }else if(caracter_lido == EOF){
                            Error::comentario_error(n_linha, n_coluna, lexema);
                        }
                    }
                    else if (caracter_lido == EOF){
                        Error::comentario_error(n_linha, n_coluna, lexema);
                    }
                    proximo_caracter();
                }
            }else{
                return Token(gramatica.DIVISAO, lexema); // é uma divisão
            }
        }

        else if(caracter_lido == '='){
            lexema.push_back(caracter_lido);
            proximo_caracter();

            if(caracter_lido == '='){
                lexema.push_back(caracter_lido);
                proximo_caracter();

                return Token(gramatica.IGUAL, lexema);
            }

            return Token(gramatica.ATRIBUICAO, lexema);
        }

        else if(caracter_lido == '<'){
            lexema.push_back(caracter_lido);
            proximo_caracter();

            if(caracter_lido == '='){
                lexema.push_back(caracter_lido);
                proximo_caracter();

                return Token(gramatica.MENORIGUAL, lexema);
            }

            return Token(gramatica.MENOR, lexema);
        }

        else if(caracter_lido == '>'){
            lexema.push_back(caracter_lido);
            proximo_caracter();

            if(caracter_lido == '='){
                lexema.push_back(caracter_lido);
                proximo_caracter();

                return Token(gramatica.MAIORIGUAL, lexema);
            }

            return Token(gramatica.MAIOR, lexema);
        }

        else if(caracter_lido == '!'){ // ! negação ??? 
            lexema.push_back(caracter_lido);
            proximo_caracter();

            if(caracter_lido != '='){
                lexema.push_back(caracter_lido);
                proximo_caracter();
                Error::diferenca_error(n_linha, n_coluna, lexema);
            }
            
            lexema.push_back(caracter_lido);
            proximo_caracter();
            return Token(gramatica.DIFERENCA, lexema);
        }

        else if(caracter_lido == '('){
            lexema.push_back(caracter_lido);
            proximo_caracter();
            return Token(gramatica.ABREPARENTESES, lexema);
        }

        else if(caracter_lido == ')'){
            lexema.push_back(caracter_lido);
            proximo_caracter();
            return Token(gramatica.FECHAPARENTESES, lexema);
        }

        else if(caracter_lido == '{'){
            lexema.push_back(caracter_lido);
            proximo_caracter();
            return Token(gramatica.ABRECHAVE, lexema);
        }

        else if(caracter_lido == '}'){
            lexema.push_back(caracter_lido);
            proximo_caracter();
            return Token(gramatica.FECHACHAVE, lexema);
        }

        else if(caracter_lido == ';'){
            lexema.push_back(caracter_lido);
            proximo_caracter();
            return Token(gramatica.PONTOVIRGULA, lexema);
        }

        else if(caracter_lido == ','){
            lexema.push_back(caracter_lido);
            proximo_caracter();
            return Token(gramatica.VIRGULA, lexema);
        }

        lexema.push_back(caracter_lido);
        Error::caracter_invalido_error(n_linha, n_coluna, lexema);



        
    }
    return Token(gramatica.EoF, std::string("EOF"));

    
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