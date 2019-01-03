//
// Created by Dorin Keshales on 2018-12-14.
//

#include <vector>
#include <iostream>
#include "PrintCommand.h"
#include "SymbolTable.h"
#include "ParametersSeperation.h"

int PrintCommand::doCommand(vector<string>& argsAndRestScript) {
    ParametersSeperation separator;
    vector<vector<string>> expressions = separator.SplitToParameters(argsAndRestScript, 1);

    string toPrint = separator.joinStrsInRangeinVectorToSingleStr(expressions[0].begin(), expressions[0].end() - 1);
    if (toPrint[0] == '\"' && toPrint[toPrint.size() - 1] == '\"') {
        cout << toPrint.substr(1, toPrint.length() - 2) << endl;
    } else {
        cout << this->dijkstra.evaluate(expressions[0]) << endl;
    }
    return expressions[0].size();
}
/*if (symbolTable.isVarExist(expressions[0][0])) {
    cout << symbolTable.getValue(expressions[0][0]) << endl;
}*/