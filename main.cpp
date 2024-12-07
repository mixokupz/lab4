#include <iostream>
#include "csv/CSV_Parser.h"
#include <vector>
using namespace std;

int main(int argc,char** argv) {
    try {
        
        if(argc!=2){
            throw(string("No file!"));
        }
        ifstream file(argv[1]);
        if(!file.is_open()){
            throw(string("File can't be opened!"));
        }

        CsvParser<int, string> parser(file, 0);
        for (tuple<int, string> rs : parser) {
            cout << rs << endl;
        }
    }
    catch (string &error) {
        cout << "ERROR: " << error << endl;
    }
    return 0;
}