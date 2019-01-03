//
// Created by Dorin Keshales on 2018-12-15.
//

#ifndef FIRSTMILESTONE_COMMANDSINTERPRETER_H
#define FIRSTMILESTONE_COMMANDSINTERPRETER_H


#include <cstdio>
#include <vector>
#include "CommandFromStringFactory.h"
#include "SymbolTable.h"
#include <pthread.h>
using namespace std;
//Pre-declaration for proper compilation.
class CommandFromStringFactory;
/**
 * This class provides with an ability to interpret and execute a plane-control script
 * for flight gear simulator. The class dealocates all memory that it creates in it.
 */
class CommandsInterpreter {
private:
    //A pointer to symbol table which is a variables data base of a script.
    SymbolTable* symbolTable;
    //This mutex will be used for coordination with server thread.
    pthread_mutex_t* mutex;
    //This cond will be used for coordination with server thread.
    pthread_cond_t* condVariable;
    //Command-expression factory, which will be used to create command expressions.
    CommandFromStringFactory* factory;
    /**
     * The help function for LexerScript functions. Interprets one line of a script
     * which is passed in a parameter -buffer.
     * @param buffer - a script line(sequence of script words) to interpret and put each
     * word in sepereted vector.
     * @return  vector with all words as different string in buffer(part of script)
     */
    vector<string> Lexer(string buffer);
public:
    /**
     * The constructor. Initializes all required members for proper work of Commands Interpreter.
     */
    CommandsInterpreter();
    /**
     * This function interprets the script which is located at path - filePath and puts
     * each word of a script in return vector in an order of script.
     * @param filePath  / a path to a file with a script to interpret.
     * @return vector of strings which has all words of script, a next one after previous one.
     */
    vector<string> LexerScript(string filePath);

    /**
     * The function interprets a script from console.
     * @return - vector with script words from the console.
     */
    vector<string> run();
    /**
     * The function checks whether a c is a legal operator of the script language.
     * @param c - an operator to check.
     * @return true if c is a legal operator. False otherwise.
     */
    inline bool isOperator(char c);
    /**
     * The function parses and performs all script which is passed in a vector script.
     * @param script - a vector of all words in a script so that each next word goes right
     * after previous one.
     */
    void parse(vector<string> script);

};


#endif //FIRSTMILESTONE_COMMANDSINTERPRETER_H
