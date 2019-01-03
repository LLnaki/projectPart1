//
// Created by Dorin Keshales on 2018-12-14.
//

#ifndef FIRSTMILESTONE_LOOPCOMMAND_H
#define FIRSTMILESTONE_LOOPCOMMAND_H


#include "ConditionCommand.h"
/**
 * This class defines a condition command which performs its inner command by while-loop.
 * That is, while a condition is satisfied.
 */
class LoopCommand : public ConditionCommand {
public:
    LoopCommand(CommandsInterpreter* cI, SymbolTable* st, pthread_mutex_t* m, pthread_cond_t* cond):
            ConditionCommand(cI, st, m, cond) {}

    int doCommand(vector<string>& argsAndRestScript);
    ~LoopCommand(){}
};


#endif //FIRSTMILESTONE_LOOPCOMMAND_H
