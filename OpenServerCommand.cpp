//
// Created by Dorin Keshales on 2018-12-14.
//

#include <vector>
#include <queue>
#include "OpenServerCommand.h"
#include "DataReaderServer.h"
#include "pthread.h"
#include "ParametersSeperation.h"
ArgumentsForReadingProcess argumentsForReadingProcess;

/**
 * The main function of reading from Simulator thread.
 * @arg: struct ArgumentsForReadingProcess
 *
 */
void *readFromServerForProcess(void *arguments) {
    DataReaderServer dataRServer(*((ArgumentsForReadingProcess *) arguments)->dataReaderServer);
    SymbolTable* st = ((ArgumentsForReadingProcess *) arguments)->st;
    delete argumentsForReadingProcess.dataReaderServer;
    dataRServer.read(st);

    return nullptr;
}

int OpenServerCommand::doCommand(vector<string>& parametersAndRestScript) {

    ParametersSeperation separator;
    vector<vector<string>> expressions = separator.SplitToParameters(parametersAndRestScript, 2);

    int port = (int) this->dijkstra.evaluate(expressions[0]);
    int timesPerSecond = (int) this->dijkstra.evaluate(expressions[1]);

    if (port < 0 || timesPerSecond < 0) {
        __throw_invalid_argument("Invalid parameters to OpenServerCommand.");
    }

    *(this->isKeepingConnectionWithClient) = true;
    //Allocating a dataReaderServer on heap.
    DataReaderServer *dataReaderServer;
    dataReaderServer = new DataReaderServer(port, timesPerSecond,
            this->condVariable, this->mutex, this->isKeepingConnectionWithClient);

    //Creating a thread ID that will constantly reads values from the simulator.
    pthread_t processOfReadingFromServer;
    //Initializing the arguments. ->
    argumentsForReadingProcess.dataReaderServer = dataReaderServer;
    argumentsForReadingProcess.st = this->symbolTable;
    //Starting the thread that runs DataReaderServer which reads from the Simulator.
    pthread_create(&processOfReadingFromServer, nullptr, readFromServerForProcess, &argumentsForReadingProcess);
    //pthread_cond_wait(this->condVariable, this->mutex);
    this->symbolTable->tuneForCooperationWithClient();
    //Return a number of the arguments that were passed to this function(this return value will be used by Parser)
    return separator.getNumOfWordsInExpressions(expressions);
}


