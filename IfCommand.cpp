//
// Created by Dorin Keshales on 2018-12-14.
//

#include <vector>
#include "IfCommand.h"
#include "ConditionCommand.h"
#include "CommandsInterpreter.h"
#include <iostream>


int IfCommand::doCommand(vector<string> &parametersAndRestScript) {
    //An iterator that points to the end close bracket of inner commands.
    vector<string>:: iterator it = this->cutCurlyBrackets(parametersAndRestScript);
    //We will use in command  interpreterCopy because from one hand we want to use
    //the same objects to which pointers are pointing, and from the other hand
    // to change objects that were passed by value.
    CommandsInterpreter interpreterCopy(*this->commandsInterpreter);
    if (this->isConditionSatisfied()) {
        //performing inner commands.
        interpreterCopy.parse(this->innerCommands);
    }
    //This difference plus 1 is a number of words from this ifcommand to the next command,
    //considering an inner commands.
    return it - parametersAndRestScript.begin() + 1;
}
