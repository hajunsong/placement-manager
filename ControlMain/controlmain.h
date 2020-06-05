#ifndef CONTROLMAIN_H
#define CONTROLMAIN_H

#include <QObject>
#include <QCloseEvent>

#include "DataControl/datacontrol.h"
#include "MainVisionModule/mainvisionmodule.h"
#include "PlaceVisionModule/placevisionmodule.h"
#include "Dynamixel/dynamixel.h"
#include "IRRobot/irrobot.h"
#include "Conveyor/conveyor.h"

#include <pthread.h>
#include <time.h>

class ControlMain : public QObject
{
    Q_OBJECT
public:
    explicit ControlMain(QObject *parent = nullptr);
    ~ControlMain();
    void start();
    void stop();
    void run_down();
    void run_turn();
    void run_block();
    void run_cancel();
    void run_grip();
    void run_grip_release();
    void run_mover();
    void stop_mover();
    static void* mainControl(void* arg);

private:
    DataControl *dataControl;
    MainVisionModule *mainVM;
    PlaceVisionModule *placeVM;
    DxlControl *dxlControl;
    IRRobot *irRobot;
    Conveyor *conveyor;

    pthread_t mainControlThread;
    bool mainControlThreadRun;
    void run_device();
    void dxl_wait();
    void grip_wait();
signals:

public slots:


};

#endif // CONTROLMAIN_H
