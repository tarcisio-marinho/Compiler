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
    this->escopo = -1;
    this->num_t = 0;
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
    
    next_token();
    bloco();

    //next_token();
    if(look_ahead->identificador != Gramatica::EoF){
        Error::token_esperado_nao_encontrado(look_ahead, "EOF", funcao);
    }
}



void Parser::bloco(){
    std::string funcao = std::string("bloco");
    this->escopo++;
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
    
    clean_simbols(this->escopo);
    this->escopo--;
    return; 
}


void Parser::declaracao_de_variavel(){
    std::string funcao = std::string("declaracao de variavel");
    
    int type = this->tipo();

    next_token();
    if(look_ahead->identificador != Gramatica::ID)
        Error::token_esperado_nao_encontrado(look_ahead, "Identificador", funcao);


    new_simbol(new Simbol(look_ahead, type, this->escopo));
    

    next_token();
    while(look_ahead->identificador == Gramatica::VIRGULA){
        
        next_token();
        if(look_ahead->identificador != Gramatica::ID)
            Error::token_esperado_nao_encontrado(look_ahead, "Identificador", funcao);
        
        new_simbol(new Simbol(look_ahead, type, this->escopo));

        next_token();
    }

    if(look_ahead->identificador != Gramatica::PONTOVIRGULA)
        Error::token_esperado_nao_encontrado(look_ahead, ";", funcao);
    

    next_token();
}


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


std::string Parser::expressao_relacional(){
    std::string funcao = std::string("expressao relacional");
    int op;
    Expressao *t, *expr1, *expr2;

    expr1 = expressao_aritmetica();
    op = operador_relacional();
    expr2 = expressao_aritmetica();

    check_types_expressao_relacional(expr1->tipo, expr2->tipo);

    if(expr1->tipo == Gramatica::INT && expr2->tipo == Gramatica::FLOAT){
        expr1->lexema == "(float) " + expr1->lexema;
    }else if(expr1->tipo == Gramatica::FLOAT && expr2->tipo == Gramatica::INT){
        expr2->lexema == "(float) " + expr2->lexema;
    }

    t = new Expressao(novo_t());
    // gerador

    return t->lexema;
}


int Parser::operador_relacional(){
    std::string funcao = std::string("operador relacional");
    int op = -5;
    if(look_ahead->identificador == Gramatica::IGUAL ||
        look_ahead->identificador == Gramatica::DIFERENCA || 
        look_ahead->identificador == Gramatica::MAIOR ||
        look_ahead->identificador == Gramatica::MENOR ||
        look_ahead->identificador == Gramatica::MAIORIGUAL ||
        look_ahead->identificador == Gramatica::MENORIGUAL){
        op = look_ahead->identificador;
        next_token();
    }else{
        Error::token_esperado_nao_encontrado(look_ahead, "== | != | > | < | >= | <= ", funcao);
    }
    return op;
}


Expressao* Parser::termo(){
    Expressao *expr1, *expr2, *t;
    int op, tipo;




    expr1 = fator();

    while(look_ahead->identificador == Gramatica::MULTIPLICACAO || look_ahead->identificador == Gramatica::DIVISAO){
        op = look_ahead->identificador;
        next_token();
        expr2 = fator();
        tipo = check_types_termo(expr1, expr2, op);

        if(expr1->tipo == Gramatica::INT && expr2->tipo == Gramatica::FLOAT){
            expr1->lexema = "(FLOAT) " + expr1->lexema;
    
        }else if(expr1->tipo == Gramatica::FLOAT && expr2->tipo == Gramatica::INT){
            expr2->lexema == "(FLOAT) " + expr2->lexema;
        }

        t = new Expressao(tipo, novo_t());
        // gerador
        expr1 = t;
    }
    return expr1;
}


Expressao* Parser::fator(){
    std::string funcao = std::string("fator");
    Expressao *temp;
    Simbol * tempsimb;
    std::string lexema = NULL;
    int tipo = -5;

    if(look_ahead->identificador == Gramatica::ABREPARENTESES){
        
        next_token();
        temp = expressao_aritmetica();
        if(look_ahead->identificador != Gramatica::FECHAPARENTESES){
            Error::token_esperado_nao_encontrado(look_ahead, ")", funcao);
        }
        next_token();
    
    }else{
        lexema = look_ahead->lexema;
        temp = new Expressao(lexema);

        if(look_ahead->identificador == Gramatica::ID){
            tempsimb = search_simbol(look_ahead->lexema, -1);
            if(tempsimb != NULL){
                tipo = tempsimb->tipo;
            }else{
                Error::variavel_nao_declarada();
            }
            next_token();

        }else if(look_ahead->identificador == Gramatica::TIPOCHAR){
            tipo = Gramatica::TIPOCHAR;
            next_token();

        }else if(look_ahead->identificador == Gramatica::TIPOFLOAT){
            tipo = Gramatica::TIPOFLOAT;
            next_token();

        }else if(look_ahead->identificador == Gramatica::TIPOINT){
            tipo = Gramatica::TIPOINT;
            next_token();

        }else{
            Error::token_esperado_nao_encontrado(look_ahead, "identificador | tipoInt | tipoFloat | tipoChar", funcao);
        }

        temp->tipo = tipo;
        return temp;
    }
}


Expressao* Parser::expressao_aritmetica(){
    Expressao *expr1, *expr2, *t;
    int tipo;

    expr1 = termo();
    expr2 = expressao_aritmetica_recursiva();
    
    if(expr2 != NULL){
        tipo = check_types_termo(expr1, expr2, expr2->op);

        if(expr1->tipo == Gramatica::INT && expr2->tipo == Gramatica::FLOAT){
            expr1->lexema == "(float) " + expr1->lexema;
        }else if(expr1->tipo == Gramatica::FLOAT && expr2->tipo == Gramatica::INT){
            expr2->lexema = "(float) " + expr2->lexema;
        }

        t = new Expressao(tipo, novo_t());
        t->op = expr2->op;
        // gerador
    }else{
        return expr1;
    }
    
    return t;
}


Expressao * Parser::expressao_aritmetica_recursiva(){

    Expressao *expr1, *expr2, *t;
    int op, tipo;

    if(look_ahead->identificador == Gramatica::SOMA ||
        look_ahead->identificador == Gramatica::SUBTRACAO){
        op = look_ahead->identificador;
        next_token();
        expr1 = termo();
        expr2 = expressao_aritmetica_recursiva();
    }else{
        return NULL;
    }

    tipo = check_types_termo(expr1, expr2, op);

    if(expr2 != NULL){
        if(expr1->tipo == Gramatica::INT && expr2->tipo == Gramatica::FLOAT){
            expr1->lexema = "(float) " + expr1->lexema;
        }else if(expr1->tipo == Gramatica::FLOAT && expr2->tipo == Gramatica::INT){
            expr2->lexema = "(float) " + expr2->lexema;
        }

        t = new Expressao(tipo, novo_t());
        t->op = op;
        // gerador
    }else{
        expr1->op = op;
        return expr1;
    }

    return t;

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
    
    if(look_ahead->identificador != Gramatica::ID){
        Error::token_esperado_nao_encontrado(look_ahead, "identificador", funcao);
    }

    next_token();
    if(look_ahead->identificador != Gramatica::ATRIBUICAO){
        Error::token_esperado_nao_encontrado(look_ahead, "=", funcao);
    }

    next_token();
    expressao_aritmetica();

    if(look_ahead->identificador != Gramatica::PONTOVIRGULA){
        Error::token_esperado_nao_encontrado(look_ahead, ";", funcao);
    }
    next_token();
}


int Parser::tipo(){
    int tipo = look_ahead->identificador;
    if(tipo == Gramatica::TIPOINT || tipo == Gramatica::TIPOFLOAT 
        || tipo == Gramatica::TIPOCHAR){
        return tipo;
    }

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


// Semantic

void Parser::new_simbol(Simbol *s){
    if(search_simbol(s->t->lexema, s->escopo) == NULL){
        this->simbol_table.push(s);
    }else{
        Error::semantico(s->tipo);
    }
}


Simbol * Parser::search_simbol(std::string lexema, int escopo){
    std::stack<Simbol*> tmp_q = this->simbol_table; 
    
    while (!tmp_q.empty()){
        Simbol * aux = tmp_q.top();
        if(aux->t->lexema == lexema){
            if(escopo == -1){
                return aux;
            }else if(aux->escopo == escopo){
                return aux;
            }
        }

        tmp_q.pop();
    } 


    return NULL;
}


void Parser::clean_simbols(int escopo){ 
    if(!this->simbol_table.empty()){
        Simbol *aux;
        while(!simbol_table.empty() && aux->escopo == this->escopo){
            aux = this->simbol_table.top();
            if(aux->escopo == this->escopo){
                this->simbol_table.pop();
            }
        }
    }  
}


void Parser::check_types_expressao_relacional(int type1, int type2){
    if(type1 != type2 && (type1 == Gramatica::TIPOCHAR || type2 == Gramatica::TIPOCHAR)){
        Error::char_nao_opera_com_outros_tipos(type1, type2);
    }
}


void Parser::check_types_atribuicao(int type1, int type2){
    if(type1 != type2){
        if(!(type1 == Gramatica::FLOAT && type2 == Gramatica::INT)){
            Error::atribuicao_incompativel(type1, type2);
        }
    }
}


int Parser::check_types_termo(Expressao *e1, Expressao *e2, int op){
    int tipo1, tipo2;

    if(e2 != NULL){
        tipo2 = e2->tipo;
        tipo1 = e1->tipo;

        if(tipo1 == tipo2 && tipo1 == Gramatica::CHAR){
            return e1->tipo;
        }else if(tipo1 == Gramatica::CHAR || tipo2 == Gramatica::CHAR){
            Error::char_nao_opera_com_outros_tipos();
        }else if(op == Gramatica::DIVISAO){
            return Gramatica::FLOAT;
        }else if(tipo1 == Gramatica::FLOAT|| tipo2 == Gramatica::FLOAT){
            return Gramatica::FLOAT;
        }
        return Gramatica::INT;
    }else{
        return e1->tipo;
    }
}


std::string Parser::novo_t(){
        return "T" + this->num_t++;
}