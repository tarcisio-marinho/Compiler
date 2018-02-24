#include "scanner.h"
#include <iostream>
#include <string>

using namespace std;

void error(const string& message){
    cout << "Error: " << message << endl;
    exit(-1);
}

int main(int argc, char * argv[]){
    if(argc < 2){
        string program_name = string(argv[0]) += ": no input files\ncompilation terminated.";
        error(program_name);

    }else{
        FILE *f = fopen(argv[1], "r");
        if(f == NULL){
            string file_name = string(argv[1]) += ": no such file or directory";
            error(file_name);
        
        }
        
    }
}