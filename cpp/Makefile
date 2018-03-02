CC=g++
OUTPUT=main
RM=rm
TESTE=teste.c
VERSION=-std=c++11

out: main regular-exp scanner token error
	$(CC) bin/main.o bin/regular-exp.o bin/scanner.o bin/token.o bin/error.o -o $(OUTPUT) $(VERSION)

main: main.cpp 
	$(CC) -c main.cpp -o bin/main.o $(VERSION)

regular-exp: regular-exp.cpp regular-exp.h
	$(CC) -c regular-exp.cpp -o bin/regular-exp.o $(VERSION)

scanner: scanner.cpp scanner.h 
	$(CC) -c scanner.cpp -o bin/scanner.o $(VERSION)

token: token.cpp token.h
	$(CC) -c token.cpp -o bin/token.o $(VERSION)

error: error.cpp error.h
	$(CC) -c error.cpp -o bin/error.o $(VERSION)

clean:
	$(RM) bin/*.o $(OUTPUT)

run:
	./$(OUTPUT) ../$(TESTE)