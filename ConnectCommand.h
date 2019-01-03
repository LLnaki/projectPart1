//
// Created by Dorin Keshales on 2018-12-14.
//

#ifndef FIRSTMILESTONE_CONNECTCOMMAND_H
#define FIRSTMILESTONE_CONNECTCOMMAND_H


#include "Command.h"
#include <pthread.h>
/**
 * This class defines a command which connects a current program as a client
 * to flight-gear simulator(as client)
 */
class ConnectCommand : public Command {
private:
    //The mutex is needed for coordination between server(simulator) and this program(client)
    pthread_mutex_t* mutex;
    //The cond is needed for coordination between server(simulator) and this program(client)
    pthread_cond_t* condVariable;
public:
    ConnectCommand(SymbolTable* st, pthread_mutex_t* m, pthread_cond_t* cond):Command(st) {
        this->mutex = m;
        this->condVariable = cond;
    }
    int doCommand(vector<string>& argumentsAndRestScript);
    ~ConnectCommand() = default;

};


#endif //FIRSTMILESTONE_CONNECTCOMMAND_H
