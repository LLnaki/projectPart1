//
// Created by Dorin Keshales on 2018-12-19.
//

#ifndef FIRSTMILESTONE_DATAREADERSERVER_H
#define FIRSTMILESTONE_DATAREADERSERVER_H


#include <map>
#include <string>
#include <pthread.h>
#include "SymbolTable.h"

#define BUFFER_SIZE 1024
#define NUM_OF_PASSED_VALUES 23
using namespace std;

//The class reads from
class DataReaderServer {

private:
    bool* isReadingActivated;
    int port;
    int timesOfReadingPerSecond;
    pthread_cond_t* condVariable;
    pthread_mutex_t* mutex;
    void setValueFromServer(double val, int index, SymbolTable* symbolTable);
    bool adjustRecievedData(SymbolTable* symbolTable, char* buffer, vector<string>& destinationVector);

public:

    DataReaderServer(int portNumber, int timesOfReadingInSec, pthread_cond_t* cond,
            pthread_mutex_t* m ,bool* isReadingAct );


    void read(SymbolTable* symbolTable);


};

#endif //FIRSTMILESTONE_DATAREADERSERVER_H
