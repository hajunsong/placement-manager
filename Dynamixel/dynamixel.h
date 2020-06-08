#ifndef DYNAMIXELLIB_H
#define DYNAMIXELLIB_H

#if defined(__linux__) || defined(__APPLE__)
#include <fcntl.h>
#include <termios.h>
#define STDIN_FILENO 0
#elif defined(_WIN32) || defined(_WIN64)
#include <conio.h>
#endif

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string>
#include <iostream>
#include <pthread.h>
#include "dynamixel_sdk/dynamixel_sdk.h"

using namespace std;

#include "DataControl/datacontrol.h"

const uint16_t ADDR_PRO_TORQUE_ENABLE = 562;
const uint16_t ADDR_PRO_GOAL_POSITION = 596;
const uint16_t ADDR_PRO_PRESENT_POSITION = 611;
const uint16_t ADDR_PRO_PRESENT_VELOCITY = 615;
const uint16_t ADDR_PRO_OPERATING_MODE = 11;
const uint16_t ADDR_PRO_LED_BLUE = 565;
const uint16_t ADDR_PRO_LED_RED = 563;
const uint16_t ADDR_PRO_LED_GREEN = 564;
const uint16_t ADDR_PRO_RETURN_DELAY_TIME = 9;

const uint16_t ADDR_INDIRECTADDRESS_FOR_READ = 49;
const uint16_t ADDR_INDIRECTDATA_FOR_READ = 634;

const uint8_t LEN_PRESENT_POSITION = 4;
const uint8_t LEN_PRESENT_VELOCITY = 4;
const uint8_t LEN_INDIRECTADDRESS_FOR_READ = LEN_PRESENT_POSITION + LEN_PRESENT_VELOCITY;
const uint8_t LEN_GOAL_POSITION = 4;

const float PROTOCOL_VERSION = 2.0;
const uint8_t DX_ID_Axis1 = 1;
const uint8_t DX_ID_Axis2 = 2;

const uint32_t BAUDRATE = 57600;
const string DEVICENAME = "/dev/ttyU2D2";

const uint8_t TORQUE_ENABLE = 1;
const uint8_t TORQUE_DISABLE = 0;

class DxlControl{
public:
    DxlControl(void* arg);
    ~DxlControl();

    void init();
    void start();
    void stop();
    static void* comm_func(void* arg);

private:
    DataControl *dataControl;

    pthread_t comm;
    bool comm_thread_run;

    dynamixel::PortHandler *portHandler;
    dynamixel::PacketHandler *packetHandler;

    int dxl_comm_result;
    uint8_t dxl_error;
    uint8_t single_id;
    bool init_flag;

    void dxl_init(uint8_t ID, uint8_t op_mode);
    void dxl_deinit(uint8_t ID);

    void getPresentPosition(uint8_t ID, int32_t *present_position_ptr);
    void getPresentVelocity(uint8_t ID, int32_t *present_velocity_ptr);
    void setTorqueEnable(uint8_t ID, uint8_t enable);

    void initGroupSyncReadIndirectAddress(uint8_t ID);
    int getGroupSyncReadIndirectAddress(int32_t *present_position, int32_t *present_velocity);

    int setGroupSyncWriteGoalPosition(int32_t *goalPosition);
};

#endif // DYNAMIXELLIB_H
