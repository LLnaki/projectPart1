//
// Created by lev on 23/12/18.
//

#ifndef FIRSTMILESTONE_DATACLIENT_H
#define FIRSTMILESTONE_DATACLIENT_H


#include <string>
#include <pthread.h>
/**
 * This class represents a socket client, which sends the values
 * to the simulator. Destructor closes the socket.
 */
class DataClient {

private:
    bool isConnected;
    int port;
    std::string ipAddressOfServer;
    int sock;
    pthread_mutex_t* mutex;
public:
    DataClient(int portNumber, std::string ipAddress,
            pthread_mutex_t* m);
    /**
     * The function establishes connection between a client and a server.
     * If a connection establishment failed, an exception is thrown.
     */
    void connect();
    /**
     * The function sends a value value to a path path in
     * simulator, if the connection was established previously.
     */
    void send(std::string path, double value);
    ~DataClient();
};


#endif //FIRSTMILESTONE_DATACLIENT_H
