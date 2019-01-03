//
// Created by Dorin Keshales on 2018-12-20.
//

#ifndef FIRSTMILESTONE_COMMANDEXPRESSION_H
#define FIRSTMILESTONE_COMMANDEXPRESSION_H


#include "Commands/Command.h"
#include <vector>

class CommandExpression : public Expression {
private:
    Command *command;
    vector<string> argsAndRestScript;
    int numOfShiftsToNextCommand;
public:
    CommandExpression(Command *command, vector<string>& argsAndRestScript);

    double calculate();
    int getNumOfShiftsToNextCommand() {
        return this->numOfShiftsToNextCommand;
    }
    ~CommandExpression() { delete this->command;}
};


#endif //FIRSTMILESTONE_COMMANDEXPRESSION_H
