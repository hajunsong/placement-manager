#ifndef IRROBOT_H
#define IRROBOT_H

#include "DataControl/datacontrol.h"

#include <pthread.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <memory.h>
using namespace std;

//#include "Exception.h"
#include "SerialPort.h"
using namespace CppLinuxSerial;

class IRRobot{
public:
    IRRobot(void* arg);
    ~IRRobot();

    void init();
    void start();
    void stop();
    static void* comm_func(void* arg);
    void setGoalPositionDual();
    void setGoalPosition(char id);
    void setMotonOffDual();
    void setMotonOff(char id);
    void getPresentPosition(char id);

private:
    DataControl *dataControl;
    SerialPort *serial;
    string txString, rxString;

    bool stateConnect;

    pthread_t comm;
    bool comm_thread_run;

    unsigned char head[3], id, size, command, address, data[3], checksum, length, data1[3], data2[3], id1, id2;

};

#endif // IRROBOT_H
