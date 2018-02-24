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
        error("no input files\ncompilation terminated.");

    }else{
        FILE *f = fopen(argv[1], "r");
        if(f == NULL){
            string name = argv[1];
            name += ": No such file or directory";
            error(name);
        
        }
        
    }
}