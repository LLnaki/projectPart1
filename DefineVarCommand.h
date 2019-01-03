//
// Created by Dorin Keshales on 2018-12-14.
//

#ifndef FIRSTMILESTONE_DEFINEVARCOMMAND_H
#define FIRSTMILESTONE_DEFINEVARCOMMAND_H


#include "Command.h"
#include <map>
/**
 * This class defines a command which declares a new variable in variable data base of the program.
 */
class DefineVarCommand : public Command {
public:
    DefineVarCommand(SymbolTable* st):Command(st) {}

    int doCommand(vector<string>& parametersAndRestScript);
    ~DefineVarCommand() = default;
};


#endif //FIRSTMILESTONE_DEFINEVARCOMMAND_H
