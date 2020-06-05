#ifndef IRROBOT_H
#define IRROBOT_H

#include "DataControl/datacontrol.h"

#include <QByteArray>
#include <QObject>
#include <QtDebug>
#include <QTimer>
#include <QThread>

#include <pthread.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
using namespace std;

//#include "Exception.h"
#include "SerialPort.h"
using namespace CppLinuxSerial;

const uint16_t IR_MOVING_STATUS_THRESHOLD = 10;
const uint16_t IR_BLOCKING_STATUS_THRESHOLD = 20;

class IRRobot : public QObject{
    Q_OBJECT
public:
    explicit IRRobot(void* arg, QObject *parent = nullptr);
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
    QByteArray txData;
    string rxString;

    bool stateConnect;

    pthread_t comm;
    bool comm_thread_run;

    unsigned char head[3], id, size, command, address, data[3], checksum, length, data1[3], data2[3], id1, id2;

};

#endif // IRROBOT_H
