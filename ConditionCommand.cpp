//
// Created by Dorin Keshales on 2018-12-14.
//

#include <vector>
#include <map>
#include "ConditionCommand.h"
#include "SymbolTable.h"
#include "Expressions/ShantingYardAlgorithem.h"
#include "ParametersSeperation.h"
#include <algorithm>
#include <iostream>
#define NUM_OF_WORDS_IN_CONDITION 3

ConditionCommand:: ConditionCommand(CommandsInterpreter* interpreter,
        SymbolTable* st, pthread_mutex_t* mut, pthread_cond_t* cond):Command(st) {
    possibleOperators["<"] = LESS_THAN;
    possibleOperators[">"] = GREATER_THAN;
    possibleOperators["<="] = LESS_OR_EQUAL_THAN;
    possibleOperators[">="] = GRATER_OR_EQUAL_THAN;
    possibleOperators["!="] = DIFFERENT_FROM;
    possibleOperators["=="] = EQUAL_TO;
    this->mutex = mut;
    this->condVariable = cond;
    this->commandsInterpreter = interpreter;
}

bool ConditionCommand::isConditionSatisfied() {
    ParametersSeperation separator;


    vector<vector<string>> expressions = separator.SplitToParameters(this->condition, NUM_OF_WORDS_IN_CONDITION);
    string conditionStr;
    //If the condition is only one sign(< or >).
    if (expressions[1].size() == 1) {
        conditionStr = expressions[1][0];
        //If the condition is two signs.
    } else if (expressions[1].size() == 2) {
        conditionStr = expressions[1][0] + expressions[1][1];
        //Comparing operator must be in size of 1 or 2. Otherwise syntax error.
    } else {
        throw "incorrect condition sign!";
    }
    if (this->possibleOperators.find(conditionStr) == this->possibleOperators.end()) {
        throw "incorrect condition sign!";
    }

    double firstVal = this->dijkstra.evaluate(expressions[0]);
    double secondVal = this->dijkstra.evaluate(expressions[2]);



    switch (this->possibleOperators.at(conditionStr)) {
        case LESS_THAN:
            return (firstVal < secondVal);
        case GREATER_THAN:
            return (firstVal > secondVal);
        case LESS_OR_EQUAL_THAN:
            return (firstVal <= secondVal);
        case GRATER_OR_EQUAL_THAN:
            return (firstVal >= secondVal);
        case DIFFERENT_FROM:
            return (firstVal != secondVal);
        case EQUAL_TO:
            return (firstVal == secondVal);
        default:
            return false;
    }
}

vector<string>::iterator ConditionCommand::cutCurlyBrackets(vector<string>& parametersAndRestScript) {
    auto it = find(parametersAndRestScript.begin(), parametersAndRestScript.end(), "{");
    if (it == parametersAndRestScript.end()) {
        __throw_runtime_error("No curly brackets.");
    }
    //If the end bracket was not found, the called function throws an exception.
    auto itOfEndOfBrackets = this->getIteratorOfClosingCurlyBracketInCondition(it + 1,
            parametersAndRestScript.end(), true);

    vector<string> condition(parametersAndRestScript.begin(), it);
    this->condition = condition;
    vector<string> theRest(it + 1, itOfEndOfBrackets);
    this->innerCommands = theRest;
    return itOfEndOfBrackets;
}

vector<string>:: iterator ConditionCommand::getIteratorOfClosingCurlyBracketInCondition(vector<string>::iterator itInScript,
        vector<string>:: iterator itOfEndOfScript, bool whetherInsideOfBrackets) {
    vector<string>::iterator itOfEndScope = find(itInScript, itOfEndOfScript, "}");
    vector<string>::iterator itOfOpenScope = find(itInScript, itOfEndOfScript, "{");
    if (itOfOpenScope < itOfEndScope) {
        itInScript = this->getIteratorOfClosingCurlyBracketInCondition(itOfOpenScope + 1,
                itOfEndOfScript, true);
    }

    if (whetherInsideOfBrackets && ( (itInScript = find(itInScript + 1, itOfEndOfScript, "}") ) == itOfEndOfScript)) {
        throw "Syntax error! Incorrect use of cur brackets.";
    }
    return itInScript;

}
