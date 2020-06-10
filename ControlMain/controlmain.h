#ifndef CONTROLMAIN_H
#define CONTROLMAIN_H

#include "DataControl/datacontrol.h"
#include "MainVisionModule/mainvisionmodule.h"
#include "PlaceVisionModule/placevisionmodule.h"
#include "Dynamixel/dynamixel.h"
#include "IRRobot/irrobot.h"
#include "Conveyor/conveyor.h"

#include <pthread.h>
#include <time.h>

class ControlMain
{
public:
    ControlMain(void* arg);
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
    static void* PVMstart(void* arg);
    static void* MVMstart(void* arg);
    static void* IRstart(void* arg);
    static void* DXLstart(void* arg);

private:
    DataControl *dataControl;
    MainVisionModule *mainVM;
    PlaceVisionModule *placeVM;
    DxlControl *dxlControl;
    IRRobot *irRobot;
    Conveyor *conveyor;

    pthread_t mainControlThread, MVM_thread, PVM_thread, IR_thread, DXL_thread;
    bool mainControlThreadRun;
    void run_device();
    void dxl_wait();
    void grip_wait(int direction);
};

#endif // CONTROLMAIN_H
