#ifndef PLACEVISIONMODULE_H
#define PLACEVISIONMODULE_H

#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cstring>
#include <arpa/inet.h>
#include <errno.h>
#include <iostream>
#include <math.h>

#include "DataControl/datacontrol.h"

using namespace std;

class PlaceVisionModule
{
public:
    PlaceVisionModule(void *arg, uint16_t portNum);
    ~PlaceVisionModule();

    void start();
    void stop();
    static void* comm_rx_func(void* arg);
    static void* comm_tx_func(void* arg);
    bool isAlive(){return comm_thread_rx_run;}

private:
    long sendByteLen;
    long byteLen;
    unsigned int curLen;
    int listenSockFD;
    int clientSockFD;
    char *ptrRecvBufIndx = nullptr;
    char buf[MAXRECEIVEBUFSIZE] = {0,};
    char bufWait[MAXWAITBUFSIZE] = {0,};
    char bufSend[5] = {0,};
    int dataLen = 0;

    DataControl *dataControl;

    pthread_t comm_tx, comm_rx;

    sockaddr_in server_addr, client_addr;
    bool comm_thread_rx_run, comm_thread_tx_run;

    uint16_t port;
};

#endif // PLACEVISIONMODULE_H
