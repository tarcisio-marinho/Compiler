#ifndef __SCANNER__
#define __SCANNER__

class Scanner{
public:
    int n_linha, n_coluna;
    char caracter_lido; 
    FILE * arquivo;
    Scanner();
    void incremento_l_c();
};


#endif