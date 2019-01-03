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
    this->symbolTable->tuneForCooperationWithClient(this->mutex);
    //Return a number of the arguments that were passed to this function(this return value will be used by Parser)
    return separator.getNumOfWordsInExpressions(expressions);
}














/*
 *     auto itCurrent = parameters.begin();
    //Get iterator that points to the end of the expression.
    auto iterThatPointsToEndOfExpr = asist.splitArgumentsToExpressions(itCurrent, parameters.end(), false);
    //Gets the string that between two iterators. This is the first argument.
    try {
        params.push(asist.joinStrsInRangeinVectorToSingleStr(itCurrent, iterThatPointsToEndOfExpr));
        //Next iterator in a vector - start of next argument.
        itCurrent = iterThatPointsToEndOfExpr + 1;
        iterThatPointsToEndOfExpr = asist.splitArgumentsToExpressions(itCurrent, parameters.end(), false);
        params.push(asist.joinStrsInRangeinVectorToSingleStr(itCurrent, iterThatPointsToEndOfExpr));
        //firstArgument is a first argument.
        //secondArgument is a second argument.
    } catch (out_of_range &e) {
        throw "Wrong number of parameters to OpenServerCommand";
    }

    Expression *first=params.pop()

    try {
        this->port=params.pop()->calculate();
    }

    for (auto itr = parameters.begin(); itr != parameters.end(); itr++) {
        for (int i = 0; i < (*itr).length(); ++i) {
            if (!isdigit((*itr)[i])) {
                throw "Wrong input to the OpenServerCommand.";
            }
        }
        if (stoi(*itr) <= 0) {
            throw "Wrong input to the OpenServerCommand.";
        }
    }

    //this->port = stoi(parameters[0]);
    //this->timesPerSecond = stoi(parameters[1]);
 */