//
// Created by lev on 15/12/18.
//
#include "DataReaderServer.h"
#include <stdio.h>
#include <stdlib.h>

#include <netdb.h>
#include <unistd.h>
#include <netinet/in.h>
#include <vector>
#include <string.h>
#include <sys/socket.h>
#include "SymbolTable.h"
#include "VarValuesPaths.h"
#include <chrono>
#include <iostream>
#define MILLISECONDS_IN_SECOND 1000
using namespace std;
    DataReaderServer:: DataReaderServer(int portNumber, int timesOfReadingInSec,
            pthread_cond_t* cond, pthread_mutex_t* m, bool* isReadingAct) :
            port(portNumber), timesOfReadingPerSecond(timesOfReadingInSec) {

    this->condVariable = cond;
    this->mutex = m;
    this->isReadingActivated = isReadingAct;
}
void DataReaderServer::read(SymbolTable* symbolTable) {
    if (!*(this->isReadingActivated)) {
        return;
    }
    int sockfd;
    int newsockfd;
    int portno;
    int clilen;
    struct sockaddr_in serv_addr, cli_addr;
    int n;

    /* First call to socket() function */
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd < 0) {
        perror("ERROR opening socket");
        exit(1);
    }

    /* Initialize socket structure */
    bzero((char *) &serv_addr, sizeof(serv_addr));
    portno = this->port;

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);

    /* Now bind the host address using bind() call.*/
    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        perror("ERROR on binding");
        exit(1);
    }

    /* Now start listening for the clients, here process will
       * go in sleep mode and will wait for the incoming connection
    */

    listen(sockfd, 5);
    clilen = sizeof(cli_addr);

    /* Accept actual connection from the client */
    newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, (socklen_t *) &clilen);
    if (newsockfd < 0) {
        perror("ERROR on accept");
        exit(1);
    }
    //pthread_cond_signal(this->condVariable);

   // chrono:: milliseconds millisecondsPerSecond(MILLISECONDS_IN_SECOND);

   // int counter = 0;
   // auto start = chrono::steady_clock::now();
   // auto end = chrono::steady_clock::now() ;
    while (*(this->isReadingActivated)) {
       // if (counter > this->timesOfReadingPerSecond &&
        //chrono::duration_cast<chrono::milliseconds>(end-start).count() < millisecondsPerSecond.count() ) {
         //   usleep((millisecondsPerSecond.count() - (end - start).count() ) / MILLISECONDS_IN_SECOND );
         //   start = chrono::steady_clock::now();
        //}
        char buffer[BUFFER_SIZE];
        /* If connection is established then start communicating */
        bzero(buffer, BUFFER_SIZE);
        int count = 0;
        n =::read(newsockfd, buffer, BUFFER_SIZE - 1);
        if (n < 0) {
            perror("ERROR reading from socket");
            exit(1);
        }
        vector<string> valuesAsStrings = symbolTable->split(string(buffer));
        //if (!this->adjustRecievedData(symbolTable, buffer, valuesAsStrings)) {
       //     continue;
      //  }
        this->adjustRecievedData(symbolTable, buffer, valuesAsStrings);

        int i = 0;

        for (auto it = valuesAsStrings.begin(); it != valuesAsStrings.end() && i < NUM_OF_PASSED_VALUES; ++it, ++i) {
            this->setValueFromServer(stod(*it), i, symbolTable);
        }
        cout<<"In DataReaderServer.cpp" << endl;
        pthread_cond_signal(this->condVariable);

        //++counter;
        //end = chrono::steady_clock::now();
    }
    close(sockfd);
    pthread_cond_signal(this->condVariable);
}

/**
 * Sets value to variables with path that has index i in order of FIle generic_smalL_XML.
 */
void
DataReaderServer::setValueFromServer(double value, int i, SymbolTable* symbolTable) {
    if (i < 0 && i >= NUM_OF_PASSED_VALUES) {
        throw "ERROR IN SETVALUEFROMSERVER FUNC";
    }
    const string pathsInOrder[NUM_OF_PASSED_VALUES] = {
            VarValuesPaths::INDICATED_SPEED_KT,
            VarValuesPaths::ALTIMETER_INDICATED_ALTITUDE_FT,
            VarValuesPaths::ALTIMETER_PRESSURE_ALT_FT,
            VarValuesPaths::INDICATED_PITCH_DEG,
            VarValuesPaths::INDICATED_ROLL_DEG,
            VarValuesPaths::INTERNAL_PITCH_DEG,
            VarValuesPaths::INTERNAL_ROLL_DEG,
            VarValuesPaths::ENCODER_INDICATED_ALTITUDE_FT,
            VarValuesPaths::ENCODER_PRESSURE_ALT_FT,
            VarValuesPaths::GPS_INDICATED_ALTITUDE_FT,
            VarValuesPaths::INDICATED_GROUND_SPEED_KT,
            VarValuesPaths::INDICATED_VERTICAL_STRING,
            VarValuesPaths::HEADING_INDICATOR_INDICATED_HEADING_DEG,
            VarValuesPaths::MAGNETIC_COMPASS_INDICATED_HEADING_DEG,
            VarValuesPaths::INDICATED_SLIP_SKID,
            VarValuesPaths::INDICATED_TURN_RATE,
            VarValuesPaths::INDICATED_SPEED_FPM,
            VarValuesPaths::FLIGHT_AILERON,
            VarValuesPaths::FLIGHT_ELEVATOR,
            VarValuesPaths::FLIGHT_RUDDER,
            VarValuesPaths::FLIGHT_FLAPS,
            VarValuesPaths::ENGINE_THROTTLE,
            VarValuesPaths::ENGINE_RPM
    };
    vector<string> variables(symbolTable->getVarValuesPaths()->getVariablesOfPath(pathsInOrder[i]));
    for (auto it = variables.begin(); it != variables.end(); ++it) {
        symbolTable->setValue(*it, value);
    }
}

bool DataReaderServer::adjustRecievedData(SymbolTable* symbolTable,
        char buffer[BUFFER_SIZE], vector<string>& destinationVector) {
    int indexOfEndLineChar1 = -1;
    int indexOfEndLineChar2 = -1;
    for(int i = 0; i < BUFFER_SIZE; ++i) {
        if (buffer[i] == '\n' && indexOfEndLineChar1 == -1) {
            indexOfEndLineChar1 = i;
        } else if (buffer[i] == '\n') {
            indexOfEndLineChar2 = i;
            break;
        }
    }
    char resultInChars[BUFFER_SIZE];
    int j = 0;
    if (indexOfEndLineChar1 != -1 && indexOfEndLineChar2 != -1) {
        for (int i = indexOfEndLineChar1 + 1; i <= indexOfEndLineChar2 - 1; ++i, ++j) {
            resultInChars[j] = buffer[i];
        }
        string correctedBufString = resultInChars;
        destinationVector = symbolTable->split(correctedBufString);
        return true;
    } else {
        return false;
    }



}
