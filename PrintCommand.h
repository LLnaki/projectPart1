//
// Created by Dorin Keshales on 2018-12-14.
//

#ifndef FIRSTMILESTONE_PRINTCOMMAND_H
#define FIRSTMILESTONE_PRINTCOMMAND_H


#include "Command.h"

/**
 * The command that prints to console a provided string/variable/value
 */
class PrintCommand : public Command {
public:
    PrintCommand(SymbolTable* st):Command(st) {}
    int doCommand(vector<string>& argsAndRestScript);
    ~PrintCommand() {}
};


#endif //FIRSTMILESTONE_PRINTCOMMAND_H
