//
// Created by lev on 23/12/18.
//

#include "DataClient.h"
#include <stdio.h>
#include <stdlib.h>

#include <netdb.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <math.h>
#include <algorithm>
#include <sstream>
#include <vector>


using namespace std;
    DataClient:: DataClient(int portNumber, std::string ipAddress,
           pthread_mutex_t* m) : port(portNumber),
                                                      isConnected(false),
                                                      ipAddressOfServer(ipAddress) {
    this->mutex = m;
};
void DataClient::connect() {
    this->sock = 0;
    struct sockaddr_in serv_addr;
    if ((this->sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n Socket creation error \n");
        throw "error";
    }

    memset(&serv_addr, '0', sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(this->port);

    // Convert IPv4 and IPv6 addresses from text to binary form
    if (inet_pton(AF_INET, this->ipAddressOfServer.data(), &serv_addr.sin_addr) <= 0) {
        printf("\nInvalid address/ Address not supported \n");
        throw "error";
    }

    if (::connect(this->sock, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        printf("\nConnection Failed \n");
        throw "error";
    }
    this->isConnected = true;
}

void DataClient::send(string path, double value) {
    if (!this->isConnected) {
        throw "Error. DataClient cannot send data being not connected to a server";
    }
    string commandToSendStr;
    commandToSendStr += "set ";
    commandToSendStr += path;
    commandToSendStr += " ";
    commandToSendStr += to_string(value);
    commandToSendStr += "\r\n";
    const char *commandToSendCharStarConst = commandToSendStr.c_str();
    int n = write(sock, commandToSendCharStarConst, strlen(commandToSendCharStarConst));
}
DataClient::~DataClient() {
    if (this->isConnected) {
        close(this->sock);
    }
}


