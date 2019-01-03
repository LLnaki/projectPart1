//
// Created by Dorin Keshales on 2018-12-22.
//

#ifndef FIRSTMILESTONE_EQUALCOMMAND_H
#define FIRSTMILESTONE_EQUALCOMMAND_H


#include "Command.h"
/**
 * This class defines a command which performs a placement of a variable with a value.
 */
class EqualCommand: public Command {
public:
    EqualCommand(SymbolTable* symbolT) : Command(symbolT) {}
    int doCommand(vector<string>& parametersAndRestScript);
    ~EqualCommand() = default;
};


#endif //FIRSTMILESTONE_EQUALCOMMAND_H
