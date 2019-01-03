//
// Created by Dorin Keshales on 2018-12-22.
//

#ifndef FIRSTMILESTONE_COMMANDFROMSTRINGFACTORY_H
#define FIRSTMILESTONE_COMMANDFROMSTRINGFACTORY_H

#include <map>
#include "Expressions/CommandExpression.h"
#include <pthread.h>
#include "CommandsInterpreter.h"
#define OPEN_DATA_SERVER "openDataServer"
#define CONNECT "connect"
#define VAR "var"
#define PRINT "print"
#define SLEEP "sleep"

#define IF "if"
#define WHILE "while"

using namespace std;
//Pre-defenition. For proper compiling.
class CommandsInterpreter;
/**
 * This class is a factory that provides a user with an ability to create command Expressions
 * and get needed data about them. Each alocated commmand expression must be deleted before creating
 * a next command expression with the function deleteLastGeneretedCommandExpression(). Also, if a user
 * wants to delete the factory and the openDataServer command was created with some command expression,
 * he must to call closeServerIfWasOpened() function.
 */
class CommandFromStringFactory {
private:
    //This is a pointer to the last created expression. It will be used to get a needed data about its behavior.
    CommandExpression* lastCommandExpression;
    //If some commands behave in special way that needs additional shifts, we will save them in this variable.
    int additionalShifts;
    //If the openDataServer command will be called, we will pass to the a mutex and cond, which are needed for a class
    //user and the server to create a required communication.
    pthread_mutex_t* mutex;
    pthread_cond_t* condVariable;
    bool* whetherServerOpened;
    //Commands interpreter which uses this factory object. It will be used to create some command expressions.
    CommandsInterpreter* commandsInterpreter;
public:
    //The constructor.
    CommandFromStringFactory(CommandsInterpreter*, pthread_mutex_t*, pthread_cond_t*);
    /**
     * The function creates a command expression according to a key word(first string in commandAndRestScript vector).
     * A key word represent a command in the script. Rightly after this command go a command's arguments.
     * @param commandAndRestScript - A rest of script which is executed now, starting from a key word of a command which
     * will be created by this function.
     * @param symbolTable - The symbol table of a current program(current script)
     * @return - a command expression which's key word appears as a fisrt string in passed part of a script
     * -  commandAndRestScript
     */
    CommandExpression *create(vector<string>& commandAndRestScript,
            SymbolTable* symbolTable);
    /**
     * @return- a number of words which must be skipped in a current script to reach a next command.
     */
    int getValueOfShiftToNextCommand();
    /**
     * The function deletes(dealocates) a last created command expression.
     */
    void deleteLastGeneretedCommandExpression();
    /**
     * The function checks whether the passed name is a legal command key word.
     * @param name -  a word to check.
     * @param symbolTable - a symbol table of the script which is running.
     * @return true - name is a key word for some command. False otherwise.
     */
    bool isCommand(string name, SymbolTable &symbolTable);
    /**
     * @return true - if a data server was opened. False otherwise.
     */
    bool whetherWasDataServerThreadOpened() { return *this->whetherServerOpened;}
    /**
     * The function closes the server and dealocated all memory that was allocated for server work.
     */
    void closeServerIfWasOpened();
};

#endif //FIRSTMILESTONE_COMMANDFROMSTRINGFACTORY_H
