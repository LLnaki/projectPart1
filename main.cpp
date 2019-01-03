#include <iostream>
#include <vector>
#include <fstream>
#include "Commands/CommandsInterpreter.h"
#include <pthread.h>
using namespace std;

int main(int argc, const char *argv[]) {
    CommandsInterpreter l;
    ifstream idFile;
    vector<string> vv;
    if (argc == 2) {
        vv = l.LexerScript(argv[1]);
    }
    l.parse(vv);
}
