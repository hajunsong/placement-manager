#include "datacontrol.h"

DataControl::DataControl(){
    TCP_ADDRESS = "192.168.0.123";
    MAIN_VISION_PORT = 2097;
    PLACE_VISION_PORT = 6666;
    
    state_state = 0;
    r_state_state = 0;
    x_offset = 0;
    y_offset = 0;
    rotation_offset = 0;
    r_x_offset = 0;
    r_y_offset = 0;
    r_rotation_offset = 0;

    repicking_object = false;
    dropped = false;
    device_operate = false;
    dropping = false;
    orderMsg = "";
    orderMsgPrev = "";
    receive_flag = false;

    present_joint_position[0] = 0;
    present_joint_position[1] = 0;

    present_joint_velocity[0] = 0;
    present_joint_velocity[1] = 0;

    desired_joint_position[0] = 0;
    desired_joint_position[1] = 0;

    DXL_Origin_Axis_1 = 0;
    DXL_Down_Axis_2 = -62045;
    DXL_Turn_Axis_1 = 131592;
    DXL_Up_Axis_2 = -125432;
    DXL_Block_Axis_2 = -65405;
    DXL_Block_Axis_1 = -13884;

    IRR_Release_Pos_1 = 0;
    IRR_Release_Pos_2 = 0;
    IRR_Grip_Pos_1 = 3000;
    IRR_Grip_Pos_2 = 3000;
    IRR_Block_Pos_1 = 1700;
    IRR_Block_Pos_2 = 1700;
    IRR_Tar_Pos_1 = 0;
    IRR_Tar_Pos_2 = 0;
    IRR_Cur_Pos_1 = 0;
    IRR_Cur_Pos_2 = 0;
    IRR_Bfr_Pos_1 = 10000;
    IRR_Bfr_Pos_2 = 10000;

    time_t now = time(0);
    struct tm tstruct;
    char buf[80];
    tstruct = *localtime(&now);
    sprintf(buf, "%04d-%02d-%02d-%02d-%02d-%02d",
            tstruct.tm_year + 1900, tstruct.tm_mon + 1, tstruct.tm_mday, tstruct.tm_hour, tstruct.tm_min, tstruct.tm_sec);

    mkdir("./logging", 0777);

    string fileName = "./logging/";
    fileName.append(buf);
    fileName.append(".txt");

    logger = new Logger(fileName);
}

DataControl::~DataControl(){
    delete logger;
}

void DataControl::dataReset()
{
    state_state = 0;
    r_state_state = 0;
    x_offset = 0;
    y_offset = 0;
    rotation_offset = 0;
    r_x_offset = 0;
    r_y_offset = 0;
    r_rotation_offset = 0;

    repicking_object = false;
    dropped = false;
    device_operate = false;
    dropping = false;
    orderMsg = "";
    orderMsgPrev = "";
    receive_flag = false;

    IRR_Release_Pos_1 = 0;
    IRR_Release_Pos_2 = 0;
    IRR_Grip_Pos_1 = 3000;
    IRR_Grip_Pos_2 = 3000;
    IRR_Block_Pos_1 = 1700;
    IRR_Block_Pos_2 = 1700;
    IRR_Tar_Pos_1 = 0;
    IRR_Tar_Pos_2 = 0;
    IRR_Cur_Pos_1 = 0;
    IRR_Cur_Pos_2 = 0;
    IRR_Bfr_Pos_1 = 0;
    IRR_Bfr_Pos_2 = 0;
}
