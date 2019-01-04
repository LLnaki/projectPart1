//
// Created by Dorin Keshales on 2018-12-22.
//

#include <vector>
#include "ShantingYardAlgorithem.h"
#include "EqualCommand.h"
#include "SymbolTable.h"
#include "CommandsInterpreter.h"
#include "ParametersSeperation.h"
#include "regex"
int EqualCommand:: doCommand(vector<string>& parametersAndRestScript) {
    regex variableFormat("\\w+");
    ParametersSeperation separator;
    vector<vector<string>> expressions = separator.SplitToParameters(parametersAndRestScript, 3);
    string var = separator.joinStrsInRangeinVectorToSingleStr(expressions[0].begin(), expressions[0].end() - 1);

    if (!this->symbolTable->isVarExist(var)) {
        __throw_invalid_argument("Variable was not found can't preform placement to a non existing variable.");
    } else if (expressions[1][0] != "=") {
        __throw_invalid_argument("Syntax error! '=' was not found while performing a placement");
    }

    string arg3 = separator.joinStrsInRangeinVectorToSingleStr(expressions[2].begin(), expressions[2].end() - 1);
    double value = this->dijkstra.evaluate(expressions[2]);
    this->symbolTable->setValue(var, value);
    //If the program is connected to the server, we will update the server with a new value of the variable.
    if (this->symbolTable->whetherIsConnectedToServer()) {
        this->symbolTable->sendToServer(var);
    }

    return separator.getNumOfWordsInExpressions(expressions);
}
