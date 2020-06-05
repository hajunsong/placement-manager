#include "controlmain.h"

ControlMain::ControlMain(QObject *parent) : QObject(parent)
{
    dataControl = new DataControl();

    mainVM = new MainVisionModule(dataControl, 2097);
    usleep(10000);
    placeVM = new PlaceVisionModule(dataControl, 6666);
    usleep(10000);

    dxlControl = new DxlControl(dataControl);
    dxlControl->init();

    irRobot = new IRRobot(dataControl);
    irRobot->init();

    conveyor = new Conveyor();

    dataControl->logger->write("=============== Application Start ==============");
}

ControlMain::~ControlMain(){
    delete placeVM;
    delete mainVM;
    delete dxlControl;
    delete irRobot;
}

void ControlMain::start(){
    dxlControl->start();
    irRobot->start();
    placeVM->start();
    mainVM->start();

    pthread_create(&mainControlThread, nullptr, mainControl, this);
}

void ControlMain::stop(){
    mainVM->stop();
    usleep(100000);
    placeVM->stop();
    usleep(100000);
    mainControlThreadRun = false;
    pthread_join(mainControlThread, nullptr);
}

void ControlMain::run_down()
{
    cout << "move down" << endl;
    dataControl->desired_joint_position[0] = dataControl->DXL_Origin_Axis_1;
    dataControl->desired_joint_position[1] = dataControl->DXL_Down_Axis_2;
    dxl_wait();
}

void ControlMain::run_turn()
{
    cout << "move down" << endl;
    dataControl->desired_joint_position[0] = dataControl->DXL_Origin_Axis_1;
    dataControl->desired_joint_position[1] = dataControl->DXL_Down_Axis_2;
    dxl_wait();

    run_grip();

    cout << "move turn" << endl;
    dataControl->desired_joint_position[0] = dataControl->DXL_Origin_Axis_1;
    dataControl->desired_joint_position[1] = dataControl->DXL_Up_Axis_2;
    dxl_wait();
    dataControl->desired_joint_position[0] = dataControl->DXL_Turn_Axis_1;
    dataControl->desired_joint_position[1] = dataControl->DXL_Up_Axis_2;
    dxl_wait();
    dataControl->desired_joint_position[0] = dataControl->DXL_Turn_Axis_1;
    dataControl->desired_joint_position[1] = dataControl->DXL_Down_Axis_2;
    dxl_wait();

    run_grip_release();

    cout << "move up" << endl;
    dataControl->desired_joint_position[0] = dataControl->DXL_Turn_Axis_1;
    dataControl->desired_joint_position[1] = dataControl->DXL_Up_Axis_2;
    dxl_wait();
    dataControl->desired_joint_position[0] = dataControl->DXL_Origin_Axis_1;
    dataControl->desired_joint_position[1] = dataControl->DXL_Up_Axis_2;
    dxl_wait();
}

void ControlMain::run_block()
{
    cout << "move grip(block)" << endl;
    dataControl->IRR_Tar_Pos_1 = dataControl->IRR_Block_Pos_1;
    dataControl->IRR_Tar_Pos_2 = dataControl->IRR_Block_Pos_2;
    grip_wait();

    cout << "move block" << endl;
    dataControl->desired_joint_position[0] = dataControl->DXL_Block_Axis_1;
    dataControl->desired_joint_position[1] = dataControl->DXL_Block_Axis_2;
    dxl_wait();
}

void ControlMain::run_cancel(){
    cout << "move cancel" << endl;
    dataControl->desired_joint_position[1] = dataControl->DXL_Up_Axis_2;
    dxl_wait();

    dataControl->desired_joint_position[0] = dataControl->DXL_Origin_Axis_1;
    dataControl->desired_joint_position[1] = dataControl->DXL_Up_Axis_2;
    dxl_wait();

    run_grip_release();
}

void ControlMain::run_grip(){
    cout << "move grip(close)" << endl;
    dataControl->IRR_Bfr_Pos_1 = 4000;
    dataControl->IRR_Bfr_Pos_2 = 4000;
    dataControl->IRR_Tar_Pos_1 = dataControl->IRR_Grip_Pos_1;
    dataControl->IRR_Tar_Pos_2 = dataControl->IRR_Grip_Pos_2;
    grip_wait();
}

void ControlMain::run_grip_release(){
    cout << "move grip(open)" << endl;
    dataControl->IRR_Bfr_Pos_1 = 4000;
    dataControl->IRR_Bfr_Pos_2 = 4000;
    dataControl->IRR_Tar_Pos_1 = dataControl->IRR_Release_Pos_1;
    dataControl->IRR_Tar_Pos_2 = dataControl->IRR_Release_Pos_2;
    grip_wait();
}

void ControlMain::run_mover(){
    cout << "move conveyor" << endl;
    conveyor->run();
    usleep(2000000);
    conveyor->stop();
}

void ControlMain::stop_mover(){
    conveyor->stop();
}

void* ControlMain::mainControl(void *arg){
    ControlMain* pThis = static_cast<ControlMain*>(arg);

    pThis->mainControlThreadRun = true;

    while(pThis->mainControlThreadRun){
        if(pThis->dataControl->receive_flag){
            if(pThis->dataControl->orderMsg.compare("repicking") == 0){
                if(pThis->dataControl->orderMsg.compare(pThis->dataControl->orderMsgPrev) != 0){
                    cout << "=============== repicking ==============" << endl;
                    pThis->dataControl->logger->write("=============== repicking ==============");
                }
            }
            if(pThis->dataControl->orderMsg.compare("drop") == 0){
                if(pThis->dataControl->orderMsg.compare(pThis->dataControl->orderMsgPrev) != 0){
                    cout << "=============== drop ==============" << endl;
                    pThis->dataControl->logger->write("=============== drop ==============");
                }
                pThis->dataControl->dropped = true;
                if(!pThis->dataControl->repicking_object){
                    pThis->dataControl->dropping = false;
                    if(!pThis->dataControl->device_operate){
                        pThis->run_device();
                    }
                    pThis->dataControl->dropping = true;
                }
                pThis->dataControl->orderMsgPrev = pThis->dataControl->orderMsg;
            }
            if(pThis->dataControl->orderMsg.compare("repicked") == 0){
                if(pThis->dataControl->orderMsg.compare(pThis->dataControl->orderMsgPrev) != 0){
                    cout << "=============== repicked ==============" << endl;
                    pThis->dataControl->logger->write("=============== repicked ==============");
                }
                if(pThis->dataControl->dropped){
                    pThis->dataControl->dropping = false;
                    if(!pThis->dataControl->device_operate){
                        pThis->run_device();
                    }
                    pThis->dataControl->dropping = true;
                    pThis->dataControl->dropped = false;
                }
                pThis->dataControl->orderMsgPrev = pThis->dataControl->orderMsg;
            }
            pThis->dataControl->orderMsg = "";

            pThis->dataControl->receive_flag = false;
        }
    }

    return nullptr;
}

void ControlMain::run_device(){
    dataControl->device_operate = true;

    if(dataControl->dropped){
        run_block();
        run_mover();
        run_cancel();
    }

    do{
        if(dataControl->state_state == 'T'){
            run_turn();
        }
        else if(dataControl->state_state == 'O' || dataControl->state_state == 'N'){
            run_cancel();
        }
    }while(dataControl->state_state == 'T');

    dataControl->device_operate = false;
}

void ControlMain::dxl_wait()
{
    cout << "dxl wait start" << endl;
    dataControl->logger->write("dxl wait start");
    while(abs(dataControl->present_joint_position[0] - dataControl->desired_joint_position[0]) > DXL_MOVING_STATUS_THRESHOLD ||
            abs(dataControl->present_joint_position[1] - dataControl->desired_joint_position[1]) > DXL_MOVING_STATUS_THRESHOLD)
    {
        usleep(1000);
//        cout << "Present Position 1 : " << dataControl->present_joint_position[0] << endl;
//        cout << "Present Position 2 : " << dataControl->present_joint_position[1] << endl;
//        cout << "Present Velocity 1 : " << dataControl->present_joint_velocity[0] << endl;
//        cout << "Present Velocity 2 : " << dataControl->present_joint_velocity[1] << endl;
//        cout << "Desired Position 1 : " << dataControl->desired_joint_position[0] << endl;
//        cout << "Desired Position 2 : " << dataControl->desired_joint_position[1] << endl;
    }
    cout << "dxl wait finish" << endl;
    dataControl->logger->write("dxl wait finish");
}

void ControlMain::grip_wait()
{
    cout << "grip wait start" << endl;
    dataControl->logger->write("grip wait start");
    int g_flgGripCnt = 0;

    while(abs(dataControl->IRR_Cur_Pos_1 - dataControl->IRR_Tar_Pos_1) > IR_MOVING_STATUS_THRESHOLD ||
          abs(dataControl->IRR_Cur_Pos_2 - dataControl->IRR_Tar_Pos_2) > IR_MOVING_STATUS_THRESHOLD)
    {
        usleep(100000);

        if(g_flgGripCnt > 3){
            if(abs(dataControl->IRR_Cur_Pos_1 - dataControl->IRR_Bfr_Pos_1) <= IR_BLOCKING_STATUS_THRESHOLD ||
                    abs(dataControl->IRR_Cur_Pos_2 - dataControl->IRR_Bfr_Pos_2) <= IR_BLOCKING_STATUS_THRESHOLD){

                irRobot->setMotonOffDual();

                dataControl->IRR_Tar_Pos_1 = dataControl->IRR_Cur_Pos_1;
                dataControl->IRR_Tar_Pos_2 = dataControl->IRR_Cur_Pos_2;
                break;
            }

            dataControl->IRR_Bfr_Pos_1 = dataControl->IRR_Cur_Pos_1;
            dataControl->IRR_Bfr_Pos_2 = dataControl->IRR_Cur_Pos_2;
        }
        g_flgGripCnt++;
    }
    cout << "grip wait finish" << endl;
    dataControl->logger->write("grip wait finish");
}
