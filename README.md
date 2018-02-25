# Compiler

Compilador para cadeira de compiladores UNICAP 

professor Silvio Bandeira


# Lexico

- letra ::= [a-z]

- dígito ::= [0-9]

- id ::= (letra | "_") (letra | "_" | dígito)*

- oprelacional ::= <  |  >  |  <=  |  >=  |  ==  |  !=

- oparitmético ::= "+"  |  "-"  |  "*"  |  "/"  |  "="

- especial ::= ")"  |  "("  |  "{"  |  "}"  |  ","  |  ";"

- palreservada ::= main  |  if  |  else  |  while  |  do  |  for  |  int  |  float  |  char

- inteiro ::= dígito+

- float ::= dígito*.dígito+

- char ::= 'letra'  |  'dígito'         // Uma constante do tipo char (entre aspas simples)
