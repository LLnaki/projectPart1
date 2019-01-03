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
    bool isDouble(const string& s);
 ;
public :
    bool whetherIsConnectedToServer() { return this->isConnectedToServer;}
    void establishConnectionToServer(int port, string ip, pthread_mutex_t* mut);
    void interruptConnectionToServer();
    SymbolTable(): isConnectedToServer(false), isClientConnectedToSymbolTable(false) {
        this->dataClientOfSymbolTable = nullptr;
        this->mutex = new pthread_mutex_t;
        pthread_mutex_init(this->mutex, nullptr);
    }
    map<string, double> GetSymbolTable();

    vector<string> split(string s);

    /**
     * This functions sets value to already existed variable in system data.
     * If string var argument is not in system data, an exception is thrown.
     * @param var- variable
     * @param value - new Value.
     */
    void setValue(string var, double value);

    double getValue(string var);

    bool isVarExist(string);

    void loadMap();

    void saveMap();
    /**
     * Binder function. it binds a new var to "keeper", which is allowed to be
     * some existing variable or some path at the server. If a path is passed,
     * it must be passed according to format "path". that is, between two '"' chars.
     * @param newVar
     * @param keeper
     */
    void bind(string newVar, string keeper);
    void createNewLinkWithNewVar(string newVar, double value);
    void createNewLinkWithNewVar(string newVar);

    VarValuesPaths *getVarValuesPaths() {
        return &this->paths;
    }

    SymbolTable *getSymbolTable() {
        return this;
    }
    void tuneForCooperationWithClient(pthread_mutex_t*);
    void sendToServer(string var);

    ~SymbolTable() {
        this->interruptConnectionToServer();
        pthread_mutex_destroy(this->mutex);
        delete this->mutex;
    }
};

#endif //FIRSTMILESTONE_SYMBOLTABLE_H
