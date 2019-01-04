//
// Created by Dorin Keshales on 2018-12-20.
//

#ifndef FIRSTMILESTONE_COMMANDEXPRESSION_H
#define FIRSTMILESTONE_COMMANDEXPRESSION_H


#include "Command.h"
#include <vector>
/**
*This class represents a command as an executable expression. CommandExpression calculcation is 
* a performing its command.
*
*/
class CommandExpression : public Expression {
private:
    Command *command;
	// arguments for a command.
    vector<string> argsAndRestScript;
	//A number of programm arguments(a number of words between this command's key word and a next command key word).
    int numOfShiftsToNextCommand;
public:
	//Constructor.
    CommandExpression(Command *command, vector<string>& argsAndRestScript);
	/**
	*The calculate function operates according to Expression interface. CommandExpression calculation is a
	*performing of a command.
	*/	
    double calculate();
	/**
	*The function returns num of words in the script between this command and a next command.
	*/
    int getNumOfShiftsToNextCommand() {
        return this->numOfShiftsToNextCommand;
    }
    ~CommandExpression() { delete this->command;}
};


#endif //FIRSTMILESTONE_COMMANDEXPRESSION_H
