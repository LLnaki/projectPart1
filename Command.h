//
// Created by Dorin Keshales on 2018-12-14.
//

#ifndef FIRSTMILESTONE_COMMAND_H
#define FIRSTMILESTONE_COMMAND_H


#include <string>
#include <list>
#include "Expressions/ShantingYardAlgorithem.h"
#include "SymbolTable.h"
#include "ParametersSeperation.h"
using namespace std;
//This is an abstract class that defines a type and behavior of Command-like object
//adapted for plane-control script for Flight-Gear Simulator.
class Command {
protected:
    //The symbol table is a basic data base for all variables in the script.
    SymbolTable* symbolTable;
    //The algorithm-object for computation a required values in command parrameters.
    ShantingYardAlgorithem dijkstra;
public:
    //Constructor.
    Command(SymbolTable* symbolT):symbolTable(symbolT),dijkstra(symbolT) {}
    /**
     * This function executes a command.
     * @param itThatPointsToParameters - a part of a script that starts from command arguments
     * and ends at the end of a script which a program executes.
     * @return a number of words in the script which are parameters for this command.
     */
    virtual int doCommand(vector<string>&  parametersAndRestScript) = 0;
    //Virtual desctructor - for derived classes.
    virtual ~Command() = default;
};


#endif //FIRSTMILESTONE_COMMAND_H
