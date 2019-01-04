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

/**
*This class represens a socket server that constantly reads data from flight-gear simulator.
*/
class DataReaderServer {

private:
	//It is a changeable bool indicatotor that says whether a server must work or it must be closed.
	//It is supposed that a user of the class have an access to this indicator(because it is a pointer).
	//And will change it to false when he will want to close the server. 
    bool* isReadingActivated;
    int port;
    int timesOfReadingPerSecond;
	//Will be used to synhronize a work with othre threads(if they are exist) in a program.
    pthread_cond_t* condVariable;
    pthread_mutex_t* mutex;
	/**
	*This function sets a recieved value from the simulator at index 'index' in buffer(values
	*expected to be recieved in CSV format and index of each value in CSV buffer appropriate to
	* prevoulsy defined order of paths in VarValuesPath constant paths).
	*/
    void setValueFromServer(double val, int index, SymbolTable* symbolTable);
	/**
	*This function adjusts a corrupted recieved data from the client (because TCP protocol is used, there
	*will be mistakes).
	*@return - vector with seperated corrected values in the order in which it was recieved from the client.
	*/
    bool adjustRecievedData(SymbolTable* symbolTable, char* buffer, vector<string>& destinationVector);

public:

    DataReaderServer(int portNumber, int timesOfReadingInSec, pthread_cond_t* cond,
            pthread_mutex_t* m ,bool* isReadingAct );

	/**
	*Creates a server that reads values 'timesOfReadingPerSecond' times per second 
	* from the simulator and updates with these values the symbol table.
	*/
    void read(SymbolTable* symbolTable);


};

#endif //FIRSTMILESTONE_DATAREADERSERVER_H
