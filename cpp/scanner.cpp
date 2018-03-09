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
            return Token(Gramatica::EoF, std::string("EOF"));
        }

        else if(Reg::is_letra(caracter_lido) || caracter_lido == '_'){
            while(Reg::is_caracter(caracter_lido) || caracter_lido == '_'){
                lexema.push_back(caracter_lido);
                proximo_caracter();
            }

            return Token(identificador_check(lexema), lexema);
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

                return Token(Gramatica::TIPOFLOAT, lexema);
            }

            return Token(Gramatica::TIPOINT, lexema);
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

            return Token(Gramatica::TIPOFLOAT, lexema);
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

            return Token(Gramatica::TIPOCHAR, lexema);
        }

        else if(caracter_lido == '+'){ // ++ += ?? 
            lexema.push_back(caracter_lido);
            proximo_caracter();
            return Token(Gramatica::SOMA, lexema);
        }

        else if(caracter_lido == '-'){ // -- -= ??
            lexema.push_back(caracter_lido);
            proximo_caracter();
            return Token(Gramatica::SUBTRACAO, lexema);
        }

        else if(caracter_lido == '*'){ // *=
            lexema.push_back(caracter_lido);
            proximo_caracter();
            return Token(Gramatica::MULTIPLICACAO, lexema);
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
                return Token(Gramatica::DIVISAO, lexema); // é uma divisão
            }
        }

        else if(caracter_lido == '='){
            lexema.push_back(caracter_lido);
            proximo_caracter();

            if(caracter_lido == '='){
                lexema.push_back(caracter_lido);
                proximo_caracter();

                return Token(Gramatica::IGUAL, lexema);
            }

            return Token(Gramatica::ATRIBUICAO, lexema);
        }

        else if(caracter_lido == '<'){
            lexema.push_back(caracter_lido);
            proximo_caracter();

            if(caracter_lido == '='){
                lexema.push_back(caracter_lido);
                proximo_caracter();

                return Token(Gramatica::MENORIGUAL, lexema);
            }

            return Token(Gramatica::MENOR, lexema);
        }

        else if(caracter_lido == '>'){
            lexema.push_back(caracter_lido);
            proximo_caracter();

            if(caracter_lido == '='){
                lexema.push_back(caracter_lido);
                proximo_caracter();

                return Token(Gramatica::MAIORIGUAL, lexema);
            }

            return Token(Gramatica::MAIOR, lexema);
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
            return Token(Gramatica::DIFERENCA, lexema);
        }

        else if(caracter_lido == '('){
            lexema.push_back(caracter_lido);
            proximo_caracter();
            return Token(Gramatica::ABREPARENTESES, lexema);
        }

        else if(caracter_lido == ')'){
            lexema.push_back(caracter_lido);
            proximo_caracter();
            return Token(Gramatica::FECHAPARENTESES, lexema);
        }

        else if(caracter_lido == '{'){
            lexema.push_back(caracter_lido);
            proximo_caracter();
            return Token(Gramatica::ABRECHAVE, lexema);
        }

        else if(caracter_lido == '}'){
            lexema.push_back(caracter_lido);
            proximo_caracter();
            return Token(Gramatica::FECHACHAVE, lexema);
        }

        else if(caracter_lido == ';'){
            lexema.push_back(caracter_lido);
            proximo_caracter();
            return Token(Gramatica::PONTOVIRGULA, lexema);
        }

        else if(caracter_lido == ','){
            lexema.push_back(caracter_lido);
            proximo_caracter();
            return Token(Gramatica::VIRGULA, lexema);
        }

        lexema.push_back(caracter_lido);
        Error::caracter_invalido_error(n_linha, n_coluna, lexema);
        
    }
    return Token(Gramatica::EoF, std::string("EOF"));

    
}


void Scanner::incremento_l_c(){
    
    if(caracter_lido == '\n'){ // new line
        n_coluna = 0; 
        n_linha +=1;
    }
    
    else if(caracter_lido == '\t')    n_coluna +=4; // tab

    else    n_coluna +=1; // normal char
    
}


void Scanner::proximo_caracter(){
    caracter_lido = (char)fgetc(arquivo);
    incremento_l_c();
}


int Scanner::identificador_check(std::string lexema){

    if(lexema == "main")    return Gramatica::MAIN;
    

    else if(lexema == "if")    return Gramatica::IF;
    

    else if(lexema == "else")    return Gramatica::ELSE;
    
    
    else if(lexema == "int")    return Gramatica::INT;
    

    else if(lexema == "float")    return Gramatica::FLOAT;
    

    else if(lexema == "char")    return Gramatica::CHAR;
    

    else if(lexema == "while")    return Gramatica::WHILE;
    
     
    else if(lexema == "do")    return Gramatica::DO;
    
    
    else if(lexema == "for")    return Gramatica::FOR;
    

    else     return Gramatica::ID;

}