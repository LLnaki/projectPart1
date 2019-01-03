//
// Created by Dorin Keshales on 2018-12-14.
//

#ifndef FIRSTMILESTONE_OPENSERVERCOMMAND_H
#define FIRSTMILESTONE_OPENSERVERCOMMAND_H


#include "Command.h"
#include "DataReaderServer.h"
#include <pthread.h>
/**
 * The struct that holds needed values for a thread of reading from the simulator.
 */
struct ArgumentsForReadingProcess {
    SymbolTable *st;
    DataReaderServer* dataReaderServer;
};
/**
 * The command wich opens a server that gets a data from a client
 * and adds it to the program.
 */
class OpenServerCommand : public Command {

private:
    pthread_cond_t* condVariable;
    pthread_mutex_t* mutex;
    //This is a bool indicator- whether server must read and continute working(true) or
    //whether it is closed(false). Changing its value from true to false will turn off the server.
    //Changing it from false to true will turn on a server only if it is a first time we turning him on.
    //That, after closing it, the server cannot be reopened by this indicator.
    bool* isKeepingConnectionWithClient;
public:
    OpenServerCommand(SymbolTable* st, pthread_mutex_t* m,
            pthread_cond_t* cond, bool* isKeepingConnectWithClient): Command(st) {
        this->condVariable = cond;
        this->mutex = m;

        this->isKeepingConnectionWithClient = isKeepingConnectWithClient;
    }
    int doCommand(vector<string>& parametersAndRestScript);
    ~OpenServerCommand() = default;

    //OpenServerCommand();
};


#endif //FIRSTMILESTONE_OPENSERVERCOMMAND_H
