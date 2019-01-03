//
// Created by lev on 15/12/18.
//


#include "Expressions/Expression.h"
#include "SymbolTable.h"
#include "CommandFromStringFactory.h"
#include "Expressions/CommandExpression.h"
#include "OpenServerCommand.h"
#include "ConnectCommand.h"
#include "DefineVarCommand.h"
#include "PrintCommand.h"
#include "IfCommand.h"
#include "LoopCommand.h"
#include "SleepCommand.h"
#include "EqualCommand.h"
CommandFromStringFactory::CommandFromStringFactory(CommandsInterpreter* cI, pthread_mutex_t* mut, pthread_cond_t* cond) {
    this->mutex = mut;
    this->condVariable = cond;
    this->additionalShifts = 1;
    this->whetherServerOpened = new bool;
    *this->whetherServerOpened = false;
    this->commandsInterpreter = cI;
    this->lastCommandExpression = nullptr;
}
//CAN BE IMPROVED, BY CREATING MAP FROM COMMAND STR TO INTEGER AND THEN USING SWITCH(WILL GIVE LOG(N) TIME)
CommandExpression *
CommandFromStringFactory::create(vector<string>& commandAndRestScript,
                                 SymbolTable *symbolTable) {
    CommandExpression* commandExpression;
    vector<string> argsAndRestScript(commandAndRestScript.begin() + 1, commandAndRestScript.end());
    if (commandAndRestScript[0] == OPEN_DATA_SERVER) {
        //Setting a bool pointer to true which will be used by server as an indicator whether to keep working.
        *this->whetherServerOpened = true;
        commandExpression = new CommandExpression(new OpenServerCommand(
                symbolTable,this->mutex, this->condVariable,this->whetherServerOpened), argsAndRestScript);
    } else if (commandAndRestScript[0] == CONNECT) {
        commandExpression =  new CommandExpression(new ConnectCommand(symbolTable,this->mutex, this->condVariable), argsAndRestScript);
    } else if (commandAndRestScript[0] == VAR) {
        commandExpression = new CommandExpression(new DefineVarCommand(symbolTable), argsAndRestScript);
    } else if (commandAndRestScript[0] == PRINT) {
        commandExpression = new CommandExpression(new PrintCommand(symbolTable), argsAndRestScript);
    } else if (commandAndRestScript[0] == IF) {
        commandExpression = new CommandExpression(new IfCommand(this->commandsInterpreter,symbolTable,
                this->mutex, this->condVariable), argsAndRestScript);
    } else if (commandAndRestScript[0] == WHILE) {
        commandExpression = new CommandExpression(new LoopCommand(this->commandsInterpreter, symbolTable,
                this->mutex, this->condVariable), argsAndRestScript);
    } else if (commandAndRestScript[0] == SLEEP) {
        commandExpression = new CommandExpression(new SleepCommand(symbolTable), argsAndRestScript);
    } else if (symbolTable->isVarExist(commandAndRestScript[0])) {
        /*
         * The fact that Equal command's first parameter is a command word in script,
         * there is no need for additional shift- a number of parrameters is a required shift.
         * */
        this->additionalShifts = 0;
        commandExpression = new CommandExpression(new EqualCommand(symbolTable),commandAndRestScript);
    } else {
        //If there is no command with such key word.
        throw invalid_argument(commandAndRestScript[0]);
    }
    //We always save previously created command expression in order to be able to get a needed information
    //about a command expression that was created.
    this->lastCommandExpression = commandExpression;
    return commandExpression;


}

bool CommandFromStringFactory::isCommand(string name, SymbolTable &symbolTable) {
    return name == OPEN_DATA_SERVER || name == CONNECT || name == VAR || name == PRINT || name == IF || name == WHILE ||
           name == SLEEP || symbolTable.isVarExist(name);
}
int CommandFromStringFactory::getValueOfShiftToNextCommand() {
    int additionalShift = this->additionalShifts;
    //Initializing;
    this->additionalShifts = 1;
    return this->lastCommandExpression->getNumOfShiftsToNextCommand() + additionalShift;
}
void CommandFromStringFactory::deleteLastGeneretedCommandExpression() {
    if (this->lastCommandExpression != nullptr) {
        delete this->lastCommandExpression;
    }
}
void CommandFromStringFactory::closeServerIfWasOpened() {
    if(this->whetherWasDataServerThreadOpened()) {
        //Waiting while a server will stop writing data before d will start checking a bool variable indicator
        //if to keep reading or not.
        pthread_cond_wait(this->condVariable, this->mutex);
        //setting an indicator as "off" in order to stop the server.
        *this->whetherServerOpened = false;
        //Waiting while the server checks the indicator and start close itself
        pthread_cond_wait(this->condVariable, this->mutex);
        delete this->whetherServerOpened;
    }
}
