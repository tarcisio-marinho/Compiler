#include "scanner.h"

Scanner::Scanner(FILE * arq){
    n_linha = 1;
    n_coluna = 0;
    caracter_lido = ' ';
    arquivo = arq;
}


Token * Scanner::scan(){
    

    while(true){
        std::string lexema = "";
        
        while(isspace(caracter_lido)){
            proximo_caracter();
        }
        
        if(caracter_lido == EOF){
            return new Token(Gramatica::EoF, std::string("EOF"), n_linha, n_coluna);
        }

        else if(Reg::is_letra(caracter_lido) || caracter_lido == '_'){
            while(Reg::is_caracter(caracter_lido) || caracter_lido == '_'){
                lexema.push_back(caracter_lido);
                proximo_caracter();
            }

            return new Token(identificador_check(lexema), lexema, n_linha, n_coluna);
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

                return new Token(Gramatica::TIPOFLOAT, lexema, n_linha, n_coluna);
            }

            return new Token(Gramatica::TIPOINT, lexema, n_linha, n_coluna);
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

            return new Token(Gramatica::TIPOFLOAT, lexema, n_linha, n_coluna);
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

            return new Token(Gramatica::TIPOCHAR, lexema, n_linha, n_coluna);
        }

        else if(caracter_lido == '+'){ // ++ += ?? 
            lexema.push_back(caracter_lido);
            proximo_caracter();
            return new Token(Gramatica::SOMA, lexema, n_linha, n_coluna);
        }

        else if(caracter_lido == '-'){ // -- -= ??
            lexema.push_back(caracter_lido);
            proximo_caracter();
            return new Token(Gramatica::SUBTRACAO, lexema, n_linha, n_coluna);
        }

        else if(caracter_lido == '*'){ // *=
            lexema.push_back(caracter_lido);
            proximo_caracter();
            return new Token(Gramatica::MULTIPLICACAO, lexema, n_linha, n_coluna);
        }

        else if(caracter_lido == '/'){
            lexema.push_back(caracter_lido);
            proximo_caracter();

            if(caracter_lido == '/'){ // comentario de uma linha
                while(caracter_lido != '\n'){
                    if(caracter_lido == EOF){
                        return new Token(Gramatica::EoF, std::string("EOF"), n_linha, n_coluna);
                    }

                    lexema.push_back(caracter_lido);
                    proximo_caracter();
                }
                continue;
            }

            else if(caracter_lido == '*'){ // comentario de multiplas linhas
                int flag = 0;
                lexema.push_back(caracter_lido);
                proximo_caracter();
                while(true){
                    
                    if(caracter_lido == '*'){
                        proximo_caracter();

                        if(caracter_lido == '/'){
                            proximo_caracter();
                            flag = 1;
                            break;
                        }
                        continue;
                    }         
                    if(caracter_lido == EOF){
                        Error::comentario_error(n_linha, n_coluna, lexema);
                    }
                    proximo_caracter();
                }

                if(flag == 1){
                    continue;
                }

            }else{
                return new Token(Gramatica::DIVISAO, lexema, n_linha, n_coluna); // é uma divisão
            }
        }

        else if(caracter_lido == '='){
            lexema.push_back(caracter_lido);
            proximo_caracter();

            if(caracter_lido == '='){
                lexema.push_back(caracter_lido);
                proximo_caracter();

                return new Token(Gramatica::IGUAL, lexema, n_linha, n_coluna);
            }

            return new Token(Gramatica::ATRIBUICAO, lexema, n_linha, n_coluna);
        }

        else if(caracter_lido == '<'){
            lexema.push_back(caracter_lido);
            proximo_caracter();

            if(caracter_lido == '='){
                lexema.push_back(caracter_lido);
                proximo_caracter();

                return new Token(Gramatica::MENORIGUAL, lexema, n_linha, n_coluna);
            }

            return new Token(Gramatica::MENOR, lexema, n_linha, n_coluna);
        }

        else if(caracter_lido == '>'){
            lexema.push_back(caracter_lido);
            proximo_caracter();

            if(caracter_lido == '='){
                lexema.push_back(caracter_lido);
                proximo_caracter();

                return new Token(Gramatica::MAIORIGUAL, lexema, n_linha, n_coluna);
            }

            return new Token(Gramatica::MAIOR, lexema, n_linha, n_coluna);
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
            return new Token(Gramatica::DIFERENCA, lexema, n_linha, n_coluna);
        }

        else if(caracter_lido == '('){
            lexema.push_back(caracter_lido);
            proximo_caracter();
            return new Token(Gramatica::ABREPARENTESES, lexema, n_linha, n_coluna);
        }

        else if(caracter_lido == ')'){
            lexema.push_back(caracter_lido);
            proximo_caracter();
            return new Token(Gramatica::FECHAPARENTESES, lexema, n_linha, n_coluna);
        }

        else if(caracter_lido == '{'){
            lexema.push_back(caracter_lido);
            proximo_caracter();
            return new Token(Gramatica::ABRECHAVE, lexema, n_linha, n_coluna);
        }

        else if(caracter_lido == '}'){
            lexema.push_back(caracter_lido);
            proximo_caracter();
            return new Token(Gramatica::FECHACHAVE, lexema, n_linha, n_coluna);
        }

        else if(caracter_lido == ';'){
            lexema.push_back(caracter_lido);
            proximo_caracter();
            return new Token(Gramatica::PONTOVIRGULA, lexema, n_linha, n_coluna);
        }

        else if(caracter_lido == ','){
            lexema.push_back(caracter_lido);
            proximo_caracter();
            return new Token(Gramatica::VIRGULA, lexema, n_linha, n_coluna);
        }

        lexema.push_back(caracter_lido);
        Error::caracter_invalido_error(n_linha, n_coluna, lexema);
        
    }
    return new Token(Gramatica::EoF, std::string("EOF"), n_linha, n_coluna);

    
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