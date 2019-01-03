//
// Created by lev on 24/12/18.
//

#include <vector>
#include <sstream>
#include "ConnectCommand.h"
#include "Expressions/ShantingYardAlgorithem.h"
#include "DataClient.h"
#include "ParametersSeperation.h"
#include <algorithm>
using namespace std;


/**
 * function which similar to the stoi function of string in java.
 *
 * @param s the requested string ti split.
 * @param delim delimiter.
 * @return a vector which holds the substrings which the comma was in between.
 */
vector<string> split(string s) {
    stringstream ss(s);
    string item;
    char p = '.';
    vector<string> elems;
    while (getline(ss, item, p)) {
        elems.push_back(item);
    }
    return elems;
}


int ConnectCommand::doCommand(vector<string>& parametersAndRestScript) {

    ParametersSeperation separator;
    vector<vector<string>> expressions = separator.SplitToParameters(parametersAndRestScript,2);

    vector<string> firstParameter = expressions[0];
    string ip = firstParameter[0];
    if (count(ip.begin(), ip.end(), '.') != 3) {
        __throw_invalid_argument("Invalid pattern of IP address to ConnectCommand");
    }
    vector<string> ipBytes = split(ip);

    if (ipBytes.size() != 4) {
        __throw_invalid_argument("Invalid pattern of IP address");
    }

    int port = (int) this->dijkstra.evaluate(expressions[1]);
    if (port < 0) {
        __throw_invalid_argument("Invalid parameter of port to ConnectCommand");
    }

    //Creates a connection between symboltable of this program and between the server.
   this->symbolTable->establishConnectionToServer(port, ip, this->mutex);

    return expressions[0].size() + expressions[1].size();
}



