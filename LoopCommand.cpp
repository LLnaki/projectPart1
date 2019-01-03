//
// Created by Dorin Keshales on 2018-12-14.
//

#include <vector>
#include "LoopCommand.h"
#include "CommandsInterpreter.h"
#include <iostream>

int LoopCommand::doCommand(vector<string>& argsAndRestScript) {
    vector<string>::iterator it = this->cutCurlyBrackets(argsAndRestScript);
    /*
     * We will use a shaly copy of interpreter because we want to change an use
     * new values of variables that were passed by value and in order to use and have
     * access to all variables that were passed by pointer(such behavior is defind by commands
     * interpreter class.
     */
    CommandsInterpreter interpreterCopy(*this->commandsInterpreter);
    while (this->isConditionSatisfied()) {
        interpreterCopy.parse(this->innerCommands);
    }
    return it - argsAndRestScript.begin() + 1;
}

