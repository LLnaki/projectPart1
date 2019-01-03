//
// Created by Dorin Keshales on 2018-12-14.
//

#include <vector>
#include "DefineVarCommand.h"
#include "ParametersSeperation.h"
#include "EqualCommand.h"
#include <regex>
#define BIND_KEY_WORD "bind"
#define VAR_FORMAT "\\w+"
#define PATH_FORMAT "\"(.+)\""

int DefineVarCommand::doCommand(vector<string>& parametersAndRestScript) {
    regex varFormat(VAR_FORMAT);
    regex pathFormat(PATH_FORMAT);
    ParametersSeperation separator;
    vector<vector<string>> expressions = separator.SplitToParameters(parametersAndRestScript,3);
    //This variable will have an iterator that points to a next command in the script.
    vector<string>:: iterator returnIt;
    string argument1 = separator.joinStrsInRangeinVectorToSingleStr(expressions[0].begin(),
            expressions[0].end() - 1);
    //first argument must be a variable.
    if(!regex_match(argument1, varFormat)) {
        throw "Syntax error! Variables must be words of alpanumeric characters";
    }
    string argument2 = separator.joinStrsInRangeinVectorToSingleStr(expressions[1].begin(),
            expressions[1].end() - 1);
    //If a second argument is not a =, it means that it is a declaration of a var without value.
    if (argument2 != "=") {
        this->symbolTable->createNewLinkWithNewVar(argument1);
        return 1;
    }
    string argument3 = separator.joinStrsInRangeinVectorToSingleStr(
            expressions[2].begin(), expressions[2].end() - 1);

    //If the bind key word appears, we will perform binding of a new variable.
    if (argument3 == BIND_KEY_WORD) {
        expressions = separator.SplitToParameters(parametersAndRestScript,4);

        string argument4 = separator.joinStrsInRangeinVectorToSingleStr(
                expressions[3].begin(), expressions[3].end() - 1);
        if (!regex_match(argument4, varFormat) && !regex_match(argument4, pathFormat)) {
            throw "Syntax error! Binder can bind only to path or to variable.";
        }
        this->symbolTable->bind(argument1, argument4);
    } else {
        this->symbolTable->createNewLinkWithNewVar(argument1);
        EqualCommand equalCommand(this->symbolTable);
        equalCommand.doCommand(parametersAndRestScript);
    }
    return separator.getNumOfWordsInExpressions(expressions);
}

