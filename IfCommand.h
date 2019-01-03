//
// Created by Dorin Keshales on 2018-12-14.
//

#ifndef FIRSTMILESTONE_IFCOMMAND_H
#define FIRSTMILESTONE_IFCOMMAND_H


#include "ConditionCommand.h"
/**
 * This class defines a ConditionCommand which only once checks its condtion, and if it is
 * satisfied, performed its inner commands.
 */
class IfCommand : public ConditionCommand {
public:
    IfCommand(CommandsInterpreter* cI, SymbolTable* st, pthread_mutex_t* m, pthread_cond_t* cond):
            ConditionCommand(cI, st, m, cond) {}
    int doCommand(vector<string> &parameters) override;
    ~IfCommand() { return;}

};


#endif //FIRSTMILESTONE_IFCOMMAND_H
