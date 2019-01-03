//
// Created by Dorin Keshales on 2018-12-14.
//

#ifndef FIRSTMILESTONE_SLEEPCOMMAND_H
#define FIRSTMILESTONE_SLEEPCOMMAND_H


#include "Command.h"

class SleepCommand : public Command {
    int miliSecSleep;
public:
    SleepCommand(SymbolTable* st):Command(st) {}
    int doCommand(vector<string>& argsAndRestSCript);
    ~SleepCommand() {}

};


#endif //FIRSTMILESTONE_SLEEPCOMMAND_H
