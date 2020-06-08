#ifndef MAINVISIOINMODULE_H
#define MAINVISIOINMODULE_H

#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cstring>
#include <arpa/inet.h>
#include <iostream>
#include <math.h>
#include <time.h>
#include <sstream>

#include "DataControl/datacontrol.h"

#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

using namespace std;
using namespace rapidjson;

class MainVisionModule
{
public:
    MainVisionModule(void *arg, uint16_t portNum);
    ~MainVisionModule();

    void start();
    void stop();
    static void* comm_rx_func(void* arg);
    static void* comm_tx_func(void* arg);
    bool isAlive(){return comm_thread_rx_run;}

private:
    long sendByteLen;
    long byteLen, len;
    unsigned int curLen;
    int listenSockFD;
    int clientSockFD;
    char *ptrRecvBufIndx = nullptr;
    char buf[MAXRECEIVEBUFSIZE] = {0,};
    char bufWait[MAXWAITBUFSIZE] = {0,};
    char bufSend[MAXSENDBUFSIZE] = {0,};

    int dataLen = 0;

    DataControl *dataControl;

    pthread_t comm_tx, comm_rx;

    Document jsonDocument;
    string orderMsg;

    sockaddr_in server_addr, client_addr;
    bool comm_thread_rx_run, comm_thread_tx_run;

    uint16_t port;
    string msg;
};

#endif // MAINVISIOINMODULE_H
