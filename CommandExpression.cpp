//
// Created by Dorin Keshales on 2018-12-20.
//

#include <vector>
#include "CommandExpression.h"

CommandExpression::CommandExpression(Command *command, vector<string>& argsAndRestScript) : command(command),
                                                                                          argsAndRestScript(
                                                                                             argsAndRestScript) {}

double CommandExpression::calculate() {
    this->numOfShiftsToNextCommand = this->command->doCommand(this->argsAndRestScript);
    return 0;
}