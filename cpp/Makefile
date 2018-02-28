CC=g++
OUTPUT=main
RM=rm
TESTE=teste.c

	
main: main.cpp 
	$(CC) -c main.cpp -o bin/main.o

regular-exp: regular-exp.cpp regular-exp.h
	$(CC) -c regular-exp.cpp -o bin/regular-exp.o

scanner: scanner.cpp scanner.h 
	$(CC) -c scanner.cpp -o bin/scanner.o

token: token.cpp token.h
	$(CC) -c token.cpp -o bin/token.o

error: error.cpp error.h
	$(CC) -c error.cpp -o bin/error.o

out: bin/main.o bin/regular-exp.o bin/scanner.o bin/token.o bin/error.o
	cd bin/
	$(CC) main.o regular-exp.o scanner.o token.o error.o -o ../$(OUTPUT)

clean:
	$(RM) bin/*.o $(OUTPUT)

run:
	./$(OUTPUT) ../$(TESTE)