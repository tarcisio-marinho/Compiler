CC=g++
OUTPUT=main
RM=rm
TESTE=teste.c
VERSION=-std=c++11

main: main.o regular-exp.o scanner.o token.o error.o parser.o simbol.o
	$(CC) main.o regular-exp.o scanner.o token.o error.o parser.o simbol.o -o $(OUTPUT) $(VERSION)

main.o: main.cpp 
	$(CC) -c main.cpp -o main.o $(VERSION)

regular-exp.o: regular-exp.cpp regular-exp.h
	$(CC) -c regular-exp.cpp -o regular-exp.o $(VERSION)

scanner.o: scanner.cpp scanner.h 
	$(CC) -c scanner.cpp -o scanner.o $(VERSION)

token.o: token.cpp token.h
	$(CC) -c token.cpp -o token.o $(VERSION)

error.o: error.cpp error.h
	$(CC) -c error.cpp -o error.o $(VERSION)

parser.o: parser.cpp parser.h
	$(CC) -c parser.cpp -o parser.o $(VERSION)

simbol.o: simbol.o simbol.h
	$(CC) -c simbol.cpp -o simbol.o $(VERSION)

clean:
	$(RM) *.o $(OUTPUT)

run:
	./$(OUTPUT) $(TESTE)