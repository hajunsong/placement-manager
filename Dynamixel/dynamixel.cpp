#include "dynamixel.h"

DxlControl::DxlControl(void *arg)
{
    dxl_comm_result = COMM_TX_FAIL;
    dxl_error = 0;
    init_flag = false;
    dataControl = static_cast<DataControl*>(arg);

    portHandler = dynamixel::PortHandler::getPortHandler("/dev/ttyDXL");
    packetHandler = dynamixel::PacketHandler::getPacketHandler(PROTOCOL_VERSION);
}

DxlControl::~DxlControl()
{
    if(init_flag){
        // Close port
        portHandler->closePort();
        printf("Closed port\n");

        delete portHandler;
        delete packetHandler;
    }
    dxl_deinit(1);
    dxl_deinit(2);

    stop();
}

void DxlControl::start(){
    while(true){
        init();
        pthread_create(&comm, nullptr, comm_func, this);
        pthread_join(comm, nullptr);
        usleep(1000000);

        string device_name = device + to_string(ttyusb++);
        cout << "Try : " << device_name << endl;
        portHandler = dynamixel::PortHandler::getPortHandler(device_name.c_str());
        packetHandler = dynamixel::PacketHandler::getPacketHandler(PROTOCOL_VERSION);
        if (ttyusb > 5)
        {
            ttyusb = 0;
        }
    }
}

void DxlControl::stop(){
    comm_thread_run = false;
    pthread_join(comm, nullptr);
}

void* DxlControl::comm_func(void *arg){
    DxlControl* pThis = static_cast<DxlControl*>(arg);

    pThis->dataControl->desired_joint_position[0] = pThis->dataControl->DXL_Origin_Axis_1;
    pThis->dataControl->desired_joint_position[1] = pThis->dataControl->DXL_Up_Axis_2;
    pThis->comm_thread_run = true;

    int status = 0;

    while(pThis->comm_thread_run){
        status = pThis->setGroupSyncWriteGoalPosition(pThis->dataControl->desired_joint_position);
        status = pThis->getGroupSyncReadIndirectAddress(pThis->dataControl->present_joint_position, pThis->dataControl->present_joint_velocity);

        if(status < 0){
            pThis->portHandler->closePort();
            printf("Closed port\n");
            pThis->comm_thread_run = false;
            pthread_exit(nullptr);
        }

//        cout << "Present Position 1 : " << pThis->dataControl->present_joint_position[0] << endl;
//        cout << "Present Position 2 : " << pThis->dataControl->present_joint_position[1] << endl;
//        cout << "Present Velocity 1 : " << pThis->dataControl->present_joint_velocity[0] << endl;
//        cout << "Present Velocity 2 : " << pThis->dataControl->present_joint_velocity[1] << endl;
//        cout << "Desired Position 1 : " << pThis->dataControl->desired_joint_position[0] << endl;
//        cout << "Desired Position 2 : " << pThis->dataControl->desired_joint_position[1] << endl;
    }

    cout << "Finish Thread Flipper Dxl Module" << endl;

    return nullptr;
}

void DxlControl::init(){

    if (portHandler->openPort()) {
        printf("Succeeded to open the port!\n");
    }
    else {
        printf("Failed to open the port!\n");
        return;
    }

    // Set port baudrate
    if (portHandler->setBaudRate(BAUDRATE)) {
        printf("Succeeded to change the baudrate!\n");
    }
    else {
        printf("Failed to change the baudrate!\n");
        return;
    }

    dxl_init(1, 3);
    dxl_init(2, 3);

    initGroupSyncReadIndirectAddress(1);
    initGroupSyncReadIndirectAddress(2);

    getGroupSyncReadIndirectAddress(dataControl->present_joint_position, dataControl->present_joint_velocity);
    cout << "Present Position 1 : " << dataControl->present_joint_position[0] << endl;
    cout << "Present Position 2 : " << dataControl->present_joint_position[1] << endl;
    cout << "Present Velocity 1 : " << dataControl->present_joint_velocity[0] << endl;
    cout << "Present Velocity 2 : " << dataControl->present_joint_velocity[1] << endl;
    dataControl->desired_joint_position[0] = dataControl->present_joint_position[0];
    dataControl->desired_joint_position[1] = dataControl->present_joint_position[1];

//    int32_t present_position1, present_position2;
//    int32_t present_velocity1, present_velocity2;
//    getPresentPosition(1, &present_position1);
//    getPresentPosition(2, &present_position2);
//    getPresentVelocity(1, &present_velocity1);
//    getPresentVelocity(2, &present_velocity2);

//    cout << present_position1 << endl;
//    cout << present_position2 << endl;
//    cout << present_velocity1 << endl;
//    cout << present_velocity2 << endl;

    setTorqueEnable(1, TORQUE_ENABLE);
    setTorqueEnable(2, TORQUE_ENABLE);

    init_flag = true;
}

void DxlControl::dxl_init(uint8_t ID, uint8_t op_mode)
{
    // Check Dynamixel Torque on or off
    uint8_t torque = 0;
    dxl_comm_result = packetHandler->read1ByteTxRx(portHandler, ID, ADDR_PRO_TORQUE_ENABLE, &torque, &dxl_error);
    if (dxl_comm_result != COMM_SUCCESS) {
        printf("[Check torque] %s\n", packetHandler->getTxRxResult(dxl_comm_result));
        return;
    }
    else if (dxl_error != 0) {
        printf("[Check torque] %s\n", packetHandler->getRxPacketError(dxl_error));
        return;
    }

    if (torque == TORQUE_ENABLE)
    {
        // Disable Dynamixel Torque
        dxl_comm_result = packetHandler->write1ByteTxRx(portHandler, ID, ADDR_PRO_TORQUE_ENABLE, TORQUE_DISABLE, &dxl_error);
        if (dxl_comm_result != COMM_SUCCESS) {
            printf("[Torque Disable] %s\n", packetHandler->getTxRxResult(dxl_comm_result));
            return;
        }
        else if (dxl_error != 0) {
            printf("[Torque Disable] %s\n", packetHandler->getRxPacketError(dxl_error));
            return;
        }
    }

    dxl_comm_result = packetHandler->write1ByteTxRx(portHandler, ID, ADDR_PRO_LED_RED, 0, &dxl_error);
    dxl_comm_result = packetHandler->write1ByteTxRx(portHandler, ID, ADDR_PRO_LED_GREEN, 0, &dxl_error);
    dxl_comm_result = packetHandler->write1ByteTxRx(portHandler, ID, ADDR_PRO_LED_BLUE, 255, &dxl_error);
    if (dxl_comm_result != COMM_SUCCESS) {
        printf("[LED on] %s\n", packetHandler->getTxRxResult(dxl_comm_result));
        return;
    }
    else if (dxl_error != 0) {
        printf("[LED on] %s\n", packetHandler->getRxPacketError(dxl_error));
        return;
    }

    // Write Dynamixel Operating mode
    dxl_comm_result = packetHandler->write1ByteTxRx(portHandler, ID, ADDR_PRO_OPERATING_MODE, op_mode, &dxl_error);
    if (dxl_comm_result != COMM_SUCCESS) {
        printf("[Operating mode] %s\n", packetHandler->getTxRxResult(dxl_comm_result));
        return;
    }
    else if (dxl_error != 0) {
        printf("[Operating mode] %s\n", packetHandler->getRxPacketError(dxl_error));
        return;
    }
    printf("[ID:%03d] operate to ", ID);
    switch(op_mode){
        case 3:
            printf("position mode\n");
            break;
        case 4:
            printf("extended position mode\n");
            break;
        default:
            break;
    }

    dxl_comm_result = packetHandler->write1ByteTxRx(portHandler, ID, ADDR_PRO_RETURN_DELAY_TIME, 20, &dxl_error);
    if (dxl_comm_result != COMM_SUCCESS) {
        printf("[Return delay time] %s\n", packetHandler->getTxRxResult(dxl_comm_result));
        return;
    }
    else if (dxl_error != 0) {
        printf("[Return delay time] %s\n", packetHandler->getRxPacketError(dxl_error));
        return;
    }

    printf("Dynamixel(ID : %d) has been successfully connected\n", ID);
}

void DxlControl::dxl_deinit(uint8_t ID)
{
    packetHandler->write1ByteTxRx(portHandler, ID, ADDR_PRO_LED_RED, 255, &dxl_error);
    packetHandler->write1ByteTxRx(portHandler, ID, ADDR_PRO_LED_GREEN, 0, &dxl_error);
    packetHandler->write1ByteTxRx(portHandler, ID, ADDR_PRO_LED_BLUE, 0, &dxl_error);

    // Disable Dynamixel Torque
    packetHandler->write1ByteTxRx(portHandler, ID, ADDR_PRO_TORQUE_ENABLE, TORQUE_DISABLE, &dxl_error);

    printf("Dynamixel has been successfully disconnected\n");
}

void DxlControl::getPresentPosition(uint8_t ID, int32_t* present_position_ptr)
{
    int32_t present_position = 0;
    dxl_comm_result = packetHandler->read4ByteTxRx(portHandler, ID, ADDR_PRO_PRESENT_POSITION, reinterpret_cast<uint32_t*>(&present_position), &dxl_error);
    if (dxl_comm_result != COMM_SUCCESS)
    {
        printf("%s\n", packetHandler->getTxRxResult(dxl_comm_result));
    }
    else if (dxl_error != 0)
    {
        printf("%s\n", packetHandler->getRxPacketError(dxl_error));
    }
    *present_position_ptr = present_position;
}

void DxlControl::getPresentVelocity(uint8_t ID, int32_t* present_velocity_ptr)
{
    int32_t present_velocity = 0;
    dxl_comm_result = packetHandler->read4ByteTxRx(portHandler, ID, ADDR_PRO_PRESENT_VELOCITY, reinterpret_cast<uint32_t*>(&present_velocity), &dxl_error);
    if (dxl_comm_result != COMM_SUCCESS)
    {
        printf("%s\n", packetHandler->getTxRxResult(dxl_comm_result));
    }
    else if (dxl_error != 0)
    {
        printf("%s\n", packetHandler->getRxPacketError(dxl_error));
    }
    *present_velocity_ptr = present_velocity;
}

void DxlControl::setTorqueEnable(uint8_t ID, uint8_t enable)
{
    // Change State Dynamixel Torque
    dxl_comm_result = packetHandler->write1ByteTxRx(portHandler, ID, ADDR_PRO_TORQUE_ENABLE, enable, &dxl_error);
    if (dxl_comm_result != COMM_SUCCESS)
    {
        printf("%s\n", packetHandler->getTxRxResult(dxl_comm_result));
    }
    else if (dxl_error != 0)
    {
        printf("%s\n", packetHandler->getRxPacketError(dxl_error));
    }
}

void DxlControl::initGroupSyncReadIndirectAddress(uint8_t ID){
    uint16_t indx = 0;
    for(uint16_t j = 0; j < LEN_PRESENT_POSITION; j++){
        dxl_comm_result = packetHandler->write2ByteTxRx(portHandler, ID, ADDR_INDIRECTADDRESS_FOR_READ + indx, ADDR_PRO_PRESENT_POSITION + j, &dxl_error);
        if (dxl_comm_result != COMM_SUCCESS)
        {
            printf("[Indirect address (present position)] %s\n", packetHandler->getTxRxResult(dxl_comm_result));
        }
        else if (dxl_error != 0)
        {
            printf("[Indirect address (present position)] %s\n", packetHandler->getRxPacketError(dxl_error));
        }
        indx += 2;
    }

    for(uint16_t j = 0; j < LEN_PRESENT_VELOCITY; j++){
        dxl_comm_result = packetHandler->write2ByteTxRx(portHandler, ID, ADDR_INDIRECTADDRESS_FOR_READ + indx, ADDR_PRO_PRESENT_VELOCITY + j, &dxl_error);
        if (dxl_comm_result != COMM_SUCCESS)
        {
            printf("[Indirect address (present velocity)] %s\n", packetHandler->getTxRxResult(dxl_comm_result));
        }
        else if (dxl_error != 0)
        {
            printf("[Indirect address (present velocity)] %s\n", packetHandler->getRxPacketError(dxl_error));
        }
        indx += 2;
    }
}

int DxlControl::getGroupSyncReadIndirectAddress(int32_t *present_position, int32_t *present_velocity){
    // Syncread present data from indirectdata
    dynamixel::GroupSyncRead groupSyncRead(portHandler, packetHandler, ADDR_INDIRECTDATA_FOR_READ, LEN_INDIRECTADDRESS_FOR_READ);

    bool dxl_addparam_result = false;	// addParam result

    for(uint8_t ID = 0; ID < 2; ID++){
        // Add parameter storage
        dxl_addparam_result = groupSyncRead.addParam(ID + 1);
        if (dxl_addparam_result != true)
        {
            printf("[ID:%03d] groupSyncRead add param failed", ID+1);
            return -1;
        }
    }

    dxl_comm_result = groupSyncRead.txRxPacket();
    if (dxl_comm_result != COMM_SUCCESS) {
        printf("%s\n", packetHandler->getTxRxResult(dxl_comm_result));
        return -1;
    }

    for (uint8_t ID = 0; ID < 2; ID++){
        // Check if groupsyncread data of Dyanamixel is available
        int dxl_getdata_result = 0;
        dxl_getdata_result = groupSyncRead.isAvailable(ID+1, ADDR_INDIRECTDATA_FOR_READ, LEN_PRESENT_POSITION);
        if (dxl_getdata_result != true)
        {
            fprintf(stderr, "[ID:%03d] groupSyncRead getdata failed\n", ID+1);
            return -1;
        }

        // Check if groupsyncread data of Dyanamixel is available
        dxl_getdata_result = groupSyncRead.isAvailable(ID+1, ADDR_INDIRECTDATA_FOR_READ + LEN_PRESENT_POSITION, LEN_PRESENT_VELOCITY);
        if (dxl_getdata_result != true)
        {
            fprintf(stderr, "[ID:%03d] groupSyncRead getdata failed\n", ID+1);
            return -1;
        }
    }

    for (uint8_t ID = 0; ID < 2; ID++){
        // Get Dynamixel present position value
        present_position[ID] = static_cast<int32_t>(groupSyncRead.getData(ID+1, ADDR_INDIRECTDATA_FOR_READ, LEN_PRESENT_POSITION));

        // Get Dynamixel present velocity value
        present_velocity[ID] = static_cast<int32_t>(groupSyncRead.getData(ID+1, ADDR_INDIRECTDATA_FOR_READ + LEN_PRESENT_POSITION, LEN_PRESENT_VELOCITY));
    }

    groupSyncRead.clearParam();

    return 0;
}

int DxlControl::setGroupSyncWriteGoalPosition(int32_t *goalPosition)
{
    dynamixel::GroupSyncWrite groupSyncWrite(portHandler, packetHandler, ADDR_PRO_GOAL_POSITION, LEN_GOAL_POSITION);
    bool dxl_addparam_result = false;	// addParam result

    for (uint8_t i = 0; i < 2; i++) {
        uint8_t param_goal_position[LEN_GOAL_POSITION];
        param_goal_position[0] = DXL_LOBYTE(DXL_LOWORD(goalPosition[i]));
        param_goal_position[1] = DXL_HIBYTE(DXL_LOWORD(goalPosition[i]));
        param_goal_position[2] = DXL_LOBYTE(DXL_HIWORD(goalPosition[i]));
        param_goal_position[3] = DXL_HIBYTE(DXL_HIWORD(goalPosition[i]));

        // Add Dynamixel#n goal position value to the Syncwrite storage
        dxl_addparam_result = groupSyncWrite.addParam(i + 1, param_goal_position);
        if (dxl_addparam_result != true)
        {
            fprintf(stderr, "[ID:%03d] groupSyncWrite add param failed", i + 1);
            return -1;
        }
    }

    // Syncwrite goal position
    dxl_comm_result = groupSyncWrite.txPacket();
    if (dxl_comm_result != COMM_SUCCESS){
        printf("%s\n", packetHandler->getTxRxResult(dxl_comm_result));
        return -1;
    }

    // Clear syncwrite parameter storage
    groupSyncWrite.clearParam();

    return 0;
}
