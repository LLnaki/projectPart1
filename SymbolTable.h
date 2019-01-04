//
// Created by Dorin Keshales on 2018-12-18.
//

#ifndef FIRSTMILESTONE_SYMBOLTABLE_H
#define FIRSTMILESTONE_SYMBOLTABLE_H

#include "map"
#include "VarValuesPaths.h"
#include "DataClient.h"
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <regex>
using namespace std;
/**
 * This class represents a variable data base in the programm that written on control-plane script.
 * It provides with an ability to use, create and adjust program variables and a connection between them.
 * It is represented using an idea of links. Each variable belongs to specific link. Each link has its value,
 * and may have a path of its location on the server. Variable's value is considered to be a value of its link and variable's path(if exist)
 * is considered to be a path of its link.
 */
class SymbolTable {





private:
    //The paths of links on the server. In paths we will save only first variable from each link.
    VarValuesPaths paths;
    //A map of links to their values for variables that already have values(were initialized).
    map<vector<string>, double> varStringToItsValue;
    //a vector of links which has no value(yet haven't been initialized)
    vector<vector<string>> linksWithoutValues;
    //DataClient that represent the client of this symbol table.
    DataClient* dataClientOfSymbolTable;
    //mutex will be used to synhronize the work between server and this symbol table, if the connection is established.
    pthread_mutex_t* mutex;
    bool isConnectedToServer;
    bool isClientConnectedToSymbolTable;
    /**
     * Creates new link according to path.
     * @param newVar
     * @param pathToWhichWeBind
     */
    void createNewLinkWithNewVar(string newVar, string pathToWhichWeBind);
    /**
     * Binds a var to existed link according to another var in this link.
     * @param newVar
     * @param anotherVarInThisLink
     */
    void bindNewVarToExistingLink(string newVar, string anotherVarInThisLink);
	/**
	*This function checks whether a passed string represents a double value.
	*/
    bool isDouble(const string& s);
 ;
public :
	/**
	*@return - true if a symbol table connected to server. False otherwise.
	*/
    bool whetherIsConnectedToServer() { return this->isConnectedToServer;}
	/**
	*The function establishes connection between this symbol table and a server.
	*according to passed as parameters port and ip address. The symbol table, after
	*performing this function,will be the client of this server and it will be able to
	*send value there.
	*/
    void establishConnectionToServer(int port, string ip, pthread_mutex_t* mut);
	/**
	*The function interrupts a connection between a server and this symbol table
	*if such a connection was established, in an accurate way. That is, it closes all
	*opened sockets and deallocates all allocated memory which was used for comunication.
	*/
    void interruptConnectionToServer();
    SymbolTable(): isConnectedToServer(false), isClientConnectedToSymbolTable(false) {
        this->dataClientOfSymbolTable = nullptr;
        this->mutex = new pthread_mutex_t;
        pthread_mutex_init(this->mutex, nullptr);
    }
	/**
	*This function returns a map from all variables in program to their values(values
	*of their links). This function hides a linking because it returns mapping between 
	*variables themselves and their values, without no reference to links.
	*
	*/
    map<string, double> GetSymbolTable();
	/**
	*The function splits a string to vector of string according to comma-seperator.
	*That is, it interprets a string of CSV type and puts CSV values to a return vector.
	*@return - a vector of strings with string-values of CSV string s(argument).
	*/
    vector<string> split(string s);

    /**
     * This functions sets value to the link of already existed variable in system data .
     * If string var argument is not in system data, an exception is thrown.
     * @param var- variable of a link. A value will be set to this link.
     * @param value - new Value.
     */
    void setValue(string var, double value);
	/**
	*Gets value of asked variable. If asked variable doesn't exist an exception is
	*thrown.
	*/
    double getValue(string var);
	/**
	*The function check is a given string is an existing variable in this symbol table.
	*@return - true if such a variable in this symbol table. Else, false.
	*/
    bool isVarExist(string);
	/**
	*Loads all links, with their variables,values and paths to this symbol table from the file.
	*/
    void loadMap();
	/**
	*Saves all links which currently are in this symbol table to the file. It is an additional feature 
	*that helps to save already used variables in previous programm executiong or even from another programm. 
	*/
    void saveMap();
    /**
     * Binder function. it binds a new var to "keeper", which is allowed to be
     * some existing variable or some path at the server. If a path is passed,
     * it must be passed according to format "path". That is, between two '"' chars.
     * @param newVar - a new variable to add to this symbol table.
     * @param keeper - a binder variable/path. A new var will be bind to a link of this keeper.
     */
    void bind(string newVar, string keeper);
	/**
	*The function creates new link in this symbol table with initial value- value.
	*/	
    void createNewLinkWithNewVar(string newVar, double value);
	/**
	*The function create a link with new var without initializing it.
	*That is, this link will have no value, and till a user will not set 
	*Some values to this link with set function, any request from a user to get
	*a value of this link will lead throwing an exception.
	*/
    void createNewLinkWithNewVar(string newVar);
	/**
	*Gets a mapping between first variables in each link 
	*and paths to which they are belong.
	*/
    VarValuesPaths *getVarValuesPaths() {
        return &this->paths;
    }
	/**
	*This function adjusts the symbol table for cooperation with client. 
	*/
    void tuneForCooperationWithClient();
	/**
	*This function sends a value of given as parameter variable 
	*to path on the server to which this variable belongs(if such a connection
	*was established).
	*/
    void sendToServer(string var);

    ~SymbolTable() {
        this->interruptConnectionToServer();
        pthread_mutex_destroy(this->mutex);
        delete this->mutex;
    }
};

#endif //FIRSTMILESTONE_SYMBOLTABLE_H
