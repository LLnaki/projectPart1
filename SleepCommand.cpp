//
// Created by Dorin Keshales on 2018-12-14.
//

#include <vector>
#include "SleepCommand.h"
#include "CommandsInterpreter.h"
#include "ParametersSeperation.h"
#include <unistd.h>
int SleepCommand::doCommand(vector<string>& argsAndRestScript) {
    ParametersSeperation separator;
    vector<vector<string>> expressions = separator.SplitToParameters(argsAndRestScript, 1);


    vector<string> milSecExpression = expressions[0];
    this->miliSecSleep = (int) dijkstra.evaluate(milSecExpression);
    if (this->miliSecSleep < 0) {
        __throw_invalid_argument("Invalid parameter to SleepCommand.");
    }
    usleep(this->miliSecSleep * 1000);
    return expressions[0].size();
}

