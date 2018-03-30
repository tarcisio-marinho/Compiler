#include "parser.h"

/*
    <decl_var> ::= <tipo> <id> {,<id>}* ";"
    
    <tipo> ::= int | float | char
    
    <programa> ::= int main"("")" <bloco>
    
    <bloco> ::= “{“ {<decl_var>}* {<comando>}* “}”
    
    <comando> ::= <comando_básico> | <iteração> | if "("<expr_relacional>")" <comando> {else <comando>}?
    
    <comando_básico> ::= <atribuição> | <bloco>
    
    <iteração> ::= while "("<expr_relacional>")" <comando> | do <comando> while "("<expr_relacional>")"";"
    
    <atribuição> ::= <id> "=" <expr_arit> ";"
    
    <expr_relacional> ::= <expr_arit> <op_relacional> <expr_arit>
    
    <expr_arit> ::= <expr_arit> "+" <termo>   | <expr_arit> "-" <termo> | <termo>
    
    <termo> ::= <termo> "*" <fator> | <termo> “/” <fator> | <fator>
    
    <fator> ::= “(“ <expr_arit> “)” | <id> | <real> | <inteiro> | <char>

*/

void Parser::next_token(){
    this->look_ahead = this->scanner->scan();
}


Parser::Parser(FILE *f){
    this->arquivo = f;
    this->scanner = new Scanner(arquivo);
}

void Parser::parse(){
    std::string funcao = std::string("main");
    next_token();
    if(look_ahead->identificador != Gramatica::INT)
        Error::token_esperado_nao_encontrado(look_ahead, "int", funcao);
    

    next_token();
    if(look_ahead->identificador != Gramatica::MAIN)
        Error::token_esperado_nao_encontrado(look_ahead, "main", funcao);
    
    
    next_token();
    if(look_ahead->identificador != Gramatica::ABREPARENTESES)
        Error::token_esperado_nao_encontrado(look_ahead, "(", funcao);
    

    next_token();
    if(look_ahead->identificador != Gramatica::FECHAPARENTESES)
        Error::token_esperado_nao_encontrado(look_ahead, ")", funcao);
    

    // Entrou no main
    next_token();
    bloco();

    next_token();
    if(look_ahead->identificador == Gramatica::EoF){
        return;
    }
}



/*
    <bloco> ::= “{“ {<decl_var>}* {<comando>}* “}”
*/
void Parser::bloco(){
    std::string funcao = std::string("bloco");
    
    if(look_ahead->identificador != Gramatica::ABRECHAVE)
        Error::token_esperado_nao_encontrado(look_ahead, "{", funcao);
    
    next_token();
    while(is_declaracao_de_variavel()) 
        declaracao_de_variavel();
    

    while(is_comando())
        comando();

    if(look_ahead->identificador != Gramatica::FECHACHAVE)
        Error::token_esperado_nao_encontrado(look_ahead, "}", funcao);

    next_token();

    return; 
}



void Parser::declaracao_de_variavel(){
    std::string funcao = std::string("declaracao de variavel");
    
    next_token();
    if(look_ahead->identificador != Gramatica::ID)
        Error::token_esperado_nao_encontrado(look_ahead, "Identificador", funcao);
    

    next_token();
    while(look_ahead->identificador == Gramatica::VIRGULA){
        
        next_token();
        if(look_ahead->identificador != Gramatica::ID)
            Error::token_esperado_nao_encontrado(look_ahead, "Identificador", funcao);
        

        next_token();
    }

    if(look_ahead->identificador != Gramatica::PONTOVIRGULA)
        Error::token_esperado_nao_encontrado(look_ahead, ";", funcao);
    

    next_token();
}
/*
    <comando> ::= <comando_básico> | <iteração> | if "("<expr_relacional>")" <comando> {else <comando>}?
*/
void Parser::comando(){
    std::string funcao = std::string("comando");
  
    if(is_comando_basico()){
        comando_basico();

    }else if(is_iteracao()){
        iteracao();
    
    }else if(look_ahead->identificador == Gramatica::IF){
        comando_if();
    
    }else{
        Error::token_esperado_nao_encontrado(look_ahead, "if | identificador | { | while | do  ", funcao);
    }
}


void Parser::comando_if(){
    std::string funcao = std::string("IF");
    if(look_ahead->identificador != Gramatica::IF){
        Error::token_esperado_nao_encontrado(look_ahead, "if", funcao);
    }

    next_token();
    if(look_ahead->identificador != Gramatica::ABREPARENTESES){
        Error::token_esperado_nao_encontrado(look_ahead, "(", funcao);
    }
    
    next_token();
    expressao_relacional();
    if(look_ahead->identificador != Gramatica::FECHAPARENTESES){
        Error::token_esperado_nao_encontrado(look_ahead, ")", funcao);
    }
    
    next_token();
    comando();

    if(look_ahead->identificador == Gramatica::ELSE){
        next_token();
        comando();
    }
}


void Parser::iteracao(){
    std::string funcao = std::string("iteracao");

    if(look_ahead->identificador == Gramatica::WHILE){
        comando_while();
    }else if(look_ahead->identificador == Gramatica::DO){
        comando_do();
    }else{
        Error::token_esperado_nao_encontrado(look_ahead, "DO | WHILE", funcao);
    }
}


void Parser::comando_while(){
    std::string funcao = std::string("comando while");
    next_token();
    if(look_ahead->identificador != Gramatica::ABREPARENTESES){
        Error::token_esperado_nao_encontrado(look_ahead, "(", funcao);
    }

    next_token();
    expressao_relacional();

    if(look_ahead->identificador != Gramatica::FECHAPARENTESES){
        Error::token_esperado_nao_encontrado(look_ahead, ")", funcao);
    }

    next_token();
    comando();
}


void Parser::comando_do(){
    std::string funcao = std::string("comando do");
    next_token();
    comando();

    if(look_ahead->identificador != Gramatica::WHILE){
        Error::token_esperado_nao_encontrado(look_ahead, "while", funcao);
    }
    
    next_token();
    if(look_ahead->identificador != Gramatica::ABREPARENTESES){
        Error::token_esperado_nao_encontrado(look_ahead, "(", funcao);
    }

    next_token();
    expressao_relacional();

    if(look_ahead->identificador != Gramatica::FECHAPARENTESES){
        Error::token_esperado_nao_encontrado(look_ahead, ")", funcao);
    }

    next_token();
    if(look_ahead->identificador != Gramatica::PONTOVIRGULA){
        Error::token_esperado_nao_encontrado(look_ahead, ";", funcao);
    }
    next_token();
}


void Parser::expressao_relacional(){
    std::string funcao = std::string("expressao relacional");
    expressao_aritmetica();
    operador_relacional();
    expressao_aritmetica();
}


void Parser::operador_relacional(){
    std::string funcao = std::string("operador relacional");
    if(look_ahead->identificador == Gramatica::IGUAL ||
        look_ahead->identificador == Gramatica::DIFERENCA || 
        look_ahead->identificador == Gramatica::MAIOR ||
        look_ahead->identificador == Gramatica::MENOR ||
        look_ahead->identificador == Gramatica::MAIORIGUAL ||
        look_ahead->identificador == Gramatica::MENORIGUAL){
        next_token();
    }else{
        Error::token_esperado_nao_encontrado(look_ahead, "== | != | > | < | >= | <= ", funcao);
    }
}


void Parser::termo(){
    fator();

    while(look_ahead->identificador == Gramatica::MULTIPLICACAO || look_ahead->identificador == Gramatica::DIVISAO){
        next_token();
        fator();
    }
    return;
}


void Parser::fator(){
    std::string funcao = std::string("fator");
    if(look_ahead->identificador == Gramatica::ABREPARENTESES){
        
        next_token();
        expressao_aritmetica();
        if(look_ahead->identificador != Gramatica::FECHAPARENTESES){
            Error::token_esperado_nao_encontrado(look_ahead, ")", funcao);
        }
        next_token();
    
    }else{
        if(look_ahead->identificador == Gramatica::ID){
            next_token();
        }else if(look_ahead->identificador == Gramatica::TIPOCHAR){
            next_token();
        }else if(look_ahead->identificador == Gramatica::TIPOFLOAT){
            next_token();
        }else if(look_ahead->identificador == Gramatica::TIPOINT){
            next_token();
        }else{
            Error::token_esperado_nao_encontrado(look_ahead, "identificador | tipoInt | tipoFloat | tipoChar", funcao);
        }
    }
}


void Parser::expressao_aritmetica(){
    termo();
    expressao_aritmetica_recursiva();
    
    return;
}


void Parser::expressao_aritmetica_recursiva(){
    if(look_ahead->identificador == Gramatica::SOMA ||
        look_ahead->identificador == Gramatica::SUBTRACAO){
        next_token();
        termo();
        expressao_aritmetica_recursiva();
    }
    return;

}


void Parser::comando_basico(){
    std::string funcao = std::string("comando basico");
    if(is_atribuicao())
        atribuicao();
    
    else if(is_bloco())
        bloco();
    
    else
        Error::token_esperado_nao_encontrado(look_ahead, "Identificador | {", funcao);
    

}



void Parser::atribuicao(){
    std::string funcao = std::string("atribuicao");
    next_token(); // ????
    next_token();
    if(look_ahead->identificador != Gramatica::ATRIBUICAO)
        Error::token_esperado_nao_encontrado(look_ahead, "=", funcao);
    
    expressao_aritmetica();

    next_token();
    if(look_ahead->identificador != Gramatica::PONTOVIRGULA)
        Error::token_esperado_nao_encontrado(look_ahead, ";", funcao);
    
    return;
}


// IS's
bool Parser::is_declaracao_de_variavel(){
    if (look_ahead->identificador == Gramatica::INT ||
        look_ahead->identificador == Gramatica::FLOAT ||
        look_ahead->identificador == Gramatica::CHAR)   
        return true;

    return false;
}


bool Parser::is_comando(){
    if(look_ahead->identificador == Gramatica::DO ||
       look_ahead->identificador == Gramatica::WHILE||
       look_ahead->identificador == Gramatica::ID ||
       look_ahead->identificador == Gramatica::IF ||
       look_ahead->identificador == Gramatica::ABRECHAVE)
        return true;
    return false;
}


bool Parser::is_comando_basico(){
    if(look_ahead->identificador == Gramatica::ID ||
       look_ahead->identificador == Gramatica::ABRECHAVE)
        return true;
    return false;
}


bool Parser::is_iteracao(){
    if(look_ahead->identificador == Gramatica::WHILE ||
        look_ahead->identificador == Gramatica::DO)
        return true;
    return false;
}

bool Parser::is_bloco(){
    if(look_ahead->identificador == Gramatica::ABRECHAVE)
        return true;
    return false;
}

bool Parser::is_atribuicao(){
    if(look_ahead->identificador == Gramatica::ID)
        return true;
    return false;
}
