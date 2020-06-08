#ifndef DATACONTROL_H
#define DATACONTROL_H
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <sys/stat.h>
#include <sys/types.h>
using namespace std;

#include "Logger/logger.h"

const int MAXCONNECTIONS = 5;
const int MAXWAITBUFSIZE = 4096;
const int MAXSENDBUFSIZE = 1024;
const int MAXRECEIVEBUFSIZE = 1024;

const uint16_t IR_MOVING_STATUS_THRESHOLD = 10;
const uint16_t IR_BLOCKING_STATUS_THRESHOLD = 20;
const string TCP_ADDRESS = "192.168.0.123";
const uint16_t DXL_MOVING_STATUS_THRESHOLD = 13000;

class DataControl
{
public:
    DataControl();
    ~DataControl();
    void dataReset();

    char state_state, r_state_state;
    double x_offset, y_offset, rotation_offset;
    double r_x_offset, r_y_offset, r_rotation_offset;
    int i_x_offset, i_y_offset, i_rotation_offset;
    int i_r_x_offset, i_r_y_offset, i_r_rotation_offset;

    bool repicking_object, dropped, device_operate, dropping;
    string orderMsg, orderMsgPrev;

    int16_t Axis1_TarPos, Axis2_TarPos, Axis1_CurPos, Axis2_CurPos;

    int32_t present_joint_position[2], present_joint_velocity[2], desired_joint_position[2];
    int32_t DXL_Origin_Axis_1, DXL_Down_Axis_2, DXL_Turn_Axis_1, DXL_Up_Axis_2, DXL_Block_Axis_2, DXL_Block_Axis_1;
    int run_command, run_step;

    int16_t IRR_Release_Pos_1, IRR_Release_Pos_2, IRR_Grip_Pos_1, IRR_Grip_Pos_2, IRR_Cur_Pos_1, IRR_Cur_Pos_2;
    int16_t IRR_Tar_Pos_1, IRR_Tar_Pos_2, IRR_Block_Pos_1, IRR_Block_Pos_2, IRR_Bfr_Pos_1, IRR_Bfr_Pos_2;

    Logger *logger;

    bool receive_flag;
};

#endif // DATACONTROL_H
