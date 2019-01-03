//
// Created by Dorin Keshales on 2018-12-14.
//

#ifndef FIRSTMILESTONE_CONDITIONPARSER_H
#define FIRSTMILESTONE_CONDITIONPARSER_H


#include <vector>
#include "Command.h"
#include <pthread.h>
#include "CommandsInterpreter.h"
enum Operators {
    LESS_THAN, GREATER_THAN, LESS_OR_EQUAL_THAN, GRATER_OR_EQUAL_THAN, DIFFERENT_FROM, EQUAL_TO
};
/**
 * This abstract class represents a command which has its own script part in a source script to execute in
 * a some way(defined by derrived classes), if the condition is satisfied.
 */
class ConditionCommand : public Command {
private:
    map<string, Operators> possibleOperators;

protected:  //I CHANGED THIS TWO MEMBERS FROM PUBLIC TO PROTECTED. PAY ATTENTION THAT IT DOESN'T LEAD TO BUGS.
    vector<string> condition;
    //The script which belongs to this condition command.
    vector<string> innerCommands;
    pthread_mutex_t* mutex;
    pthread_cond_t* condVariable;
    CommandsInterpreter* commandsInterpreter;
public:
    ConditionCommand(CommandsInterpreter* cI, SymbolTable* st, pthread_mutex_t* mut, pthread_cond_t* cond );
    /**
     * The function checks whether a condition of this condition command was satisfied.
     * @return true if a condtion was satisfied, false otherwise.
     */
    bool isConditionSatisfied();
    /**
     * The function searches for first script sub block which is located in a current script block, in which
     * this command is executed.
     * @param parametersAndRestScript a rest of source-script which starts from arguments and ends at the end of
     * source script.
     * @return  a firstly detected script sub block in parametersAndRestScript(as words of script in a vector)
     */
    vector<string>::iterator cutCurlyBrackets(vector<string> &parametersAndRestScript);
    /**
     * The function returns an iterator  of close curly bracket of a fist detected sub-block of a script in a
     * parametersAndRestScript.
     * @param itInScript  an iterator in the script from which start to search
     * @param itOfEndOfScript - an end iterator if the script.
     * @param whetherInsideOfBrackets whether parametersAndRestScript start already in some sub-block of a script.
     * @return an iterator  of close curly bracket of a fist detected sub-block of a script in a
     * parametersAndRestScript.
     */
    vector<string>:: iterator  getIteratorOfClosingCurlyBracketInCondition(vector<string>::iterator itInScript,
                                                    vector<string>:: iterator itOfEndOfScript, bool whetherInsideOfBrackets);


};


#endif //FIRSTMILESTONE_CONDITIONPARSER_H
