CC=g++
OUTPUT=main
RM=rm
TESTE=teste.c
VERSION=-std=c++11

main: bin/main.o bin/regular-exp.o bin/scanner.o bin/token.o bin/error.o
	$(CC) bin/main.o bin/regular-exp.o bin/scanner.o bin/token.o bin/error.o -o $(OUTPUT) $(VERSION)

bin/main.o: main.cpp 
	$(CC) -c main.cpp -o bin/main.o $(VERSION)

bin/regular-exp.o: regular-exp.cpp regular-exp.h
	$(CC) -c regular-exp.cpp -o bin/regular-exp.o $(VERSION)

bin/scanner.o: scanner.cpp scanner.h 
	$(CC) -c scanner.cpp -o bin/scanner.o $(VERSION)

bin/token.o: token.cpp token.h
	$(CC) -c token.cpp -o bin/token.o $(VERSION)

bin/error.o: error.cpp error.h
	$(CC) -c error.cpp -o bin/error.o $(VERSION)

clean:
	$(RM) bin/*.o $(OUTPUT)

run:
	./$(OUTPUT) $(TESTE)