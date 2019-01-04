#include <iostream>
#include <vector>
#include <fstream>
#include "CommandsInterpreter.h"
#include <pthread.h>
using namespace std;
/**
*The main function that uses CommandInterpreter and commandLine arguments to execute a script of
*the fligh-conrol language.
*@param argv - a path to a file with a script to execute. 
*/
int main(int argc, const char *argv[]) {
    CommandsInterpreter l;
    ifstream idFile;
    vector<string> vv;
    if (argc == 2) {
        vv = l.LexerScript(argv[1]);
    }
    l.parse(vv);
}
