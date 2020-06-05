#include "irrobot.h"

IRRobot::IRRobot(void *arg)
{
    dataControl = static_cast<DataControl*>(arg);

    serial = new SerialPort("/dev/ttyUSB1", BaudRate::B_115200);

    head[0] = 0xff;
    head[1] = 0xff;
    head[2] = 0xff;

    txString = "";
    rxString = "";

    stateConnect = false;
}

IRRobot::~IRRobot(){
    stop();
    serial->Close();
    cout << "Finish Flipper IR Robot Module" << endl;
}

void IRRobot::init()
{
    while(!stateConnect){
        try {
            serial->SetTimeout(100);
            serial->Open();
            stateConnect = true;
        } catch (...) {
            cout << "Error occured in serial comm. Re try connect..." << endl;
            dataControl->logger->write("Error occured in serial comm. Re try connect...");
            stateConnect = false;
            usleep(1000000);
        }
    }
}

void IRRobot::start()
{
    pthread_create(&comm, nullptr, comm_func, this);
}

void IRRobot::stop()
{
    comm_thread_run = false;
    pthread_join(comm, nullptr);
}

void* IRRobot::comm_func(void* arg){
    IRRobot* pThis = static_cast<IRRobot*>(arg);

    pThis->comm_thread_run = true;

    while(pThis->comm_thread_run && pThis->stateConnect){
        try {
            usleep(100);
            pThis->setGoalPositionDual();

            usleep(100);
            pThis->getPresentPosition(1);
            pThis->getPresentPosition(4);

    //        cout << "Present Position 1 : " << pThis->dataControl->IRR_Cur_Pos_1 << endl;
    //        cout << "Present Position 2 : " << pThis->dataControl->IRR_Cur_Pos_2 << endl;
        } catch (...) {
            cout << "Error occured in serial comm. Try reconnect..." << endl;
            pThis->dataControl->logger->write("Error occured in serial comm. Try reconnect...");
            pThis->stateConnect = false;
            pThis->serial->Close();
            pThis->init();
        }
    }

    cout << "Finish Thread Flipper IRRobot Module" << endl;

    return nullptr;
}

void IRRobot::setGoalPosition(char id){
    txString.clear();
    size = 5;
    command = 0xf3;
    address = 0x86;

    data[0] = dataControl->IRR_Tar_Pos_1 & 0x00ff;
    data[1] = dataControl->IRR_Tar_Pos_1 >> 8;

    for(int i = 0; i < 3; i++){
        txString.push_back(head[i]);
    }
    txString.push_back(id);
    txString.push_back(size);
    txString.push_back(command);
    txString.push_back(address);
    txString.push_back(data[0]);
    txString.push_back(data[1]);

    checksum = id + size + command + address + data[0] + data[1];
    checksum = (checksum & 0x000000ff)^ 0x000000ff;
    txString.push_back(checksum);
    serial->Write(txString);
}

void IRRobot::getPresentPosition(char id){
    txString.clear();
    size = 4;
    command = 0xf2;
    address = 0x8c;
    length = 0x02;

    for(int i = 0; i < 3; i++){
        txString.push_back(head[i]);
    }
    txString.push_back(id);
    txString.push_back(size);
    txString.push_back(command);
    txString.push_back(address);
    txString.push_back(length);

    checksum = id + size + command + address + length;
    checksum = (checksum & 0x000000ff)^ 0x000000ff;
    txString.push_back(checksum);
    serial->Write(txString);

    serial->Read(rxString);
    char recv_data[9] = {0,};
    memcpy(recv_data, rxString.c_str(), 9);

    char rx_checksum = 0;
    rx_checksum = recv_data[3] + recv_data[4] + recv_data[5] + recv_data[6] + recv_data[7];
    rx_checksum = (rx_checksum & 0x000000ff)^ 0x000000ff;

    if(rx_checksum == recv_data[8]){
        if(recv_data[3] == 1)
        {
            dataControl->IRR_Cur_Pos_1 = (static_cast<unsigned char>(recv_data[7]) * 256) + static_cast<unsigned char>(recv_data[6]);
        }
        else if(recv_data[3] == 4){
            dataControl->IRR_Cur_Pos_2 = (static_cast<unsigned char>(recv_data[7]) * 256) + static_cast<unsigned char>(recv_data[6]);
        }
    }
}

void IRRobot::setGoalPositionDual()
{
    txString.clear();
    id = 0xfe;
    size = 0x0A;
    command = 0x73;
    address = 0x86;
    length = 2;
    id1 = 1;
    id2 = 4;

    data1[0] = dataControl->IRR_Tar_Pos_1 & 0x00ff;
    data1[1] = dataControl->IRR_Tar_Pos_1 >> 8;
    data2[0] = dataControl->IRR_Tar_Pos_2 & 0x00ff;
    data2[1] = dataControl->IRR_Tar_Pos_2 >> 8;

    for(int i = 0; i < 3; i++){
        txString.push_back(head[i]);
    }
    txString.push_back(id);
    txString.push_back(size);
    txString.push_back(command);
    txString.push_back(address);
    txString.push_back(length);
    txString.push_back(id1);
    txString.push_back(data1[0]);
    txString.push_back(data1[1]);
    txString.push_back(id2);
    txString.push_back(data2[0]);
    txString.push_back(data2[1]);

    checksum = id + size + command + address + length + id1 + data1[0] + data1[1] + id2 + data2[0] + data2[1];
    checksum = (checksum & 0x000000ff)^ 0x000000ff;
    txString.push_back(checksum);
    serial->Write(txString);
}

void IRRobot::setMotonOffDual()
{
    txString.clear();
    id = 0xfe;
    size = 0x08;
    command = 0x73;
    address = 0x80;
    length = 1;
    id1 = 1;
    id2 = 4;

    data1[0] = 0;
    data2[0] = 0;

    for(int i = 0; i < 3; i++){
        txString.push_back(head[i]);
    }
    txString.push_back(id);
    txString.push_back(size);
    txString.push_back(command);
    txString.push_back(address);
    txString.push_back(length);
    txString.push_back(id1);
    txString.push_back(data1[0]);
    txString.push_back(id2);
    txString.push_back(data2[0]);

    checksum = id + size + command + address + length + id1 + data1[0] + id2 + data2[0];
    checksum = (checksum & 0x000000ff)^ 0x000000ff;
    txString.push_back(checksum);
    serial->Write(txString);
}

void IRRobot::setMotonOff(char id)
{
    txString.clear();
    id = 0xfe;
    size = 0x0A;
    command = 0x73;
    address = 0x80;
    length = 1;
    id1 = 1;
    id2 = 4;

    data1[0] = 0;
    data2[0] = 0;

    for(int i = 0; i < 3; i++){
        txString.push_back(head[i]);
    }
    txString.push_back(id);
    txString.push_back(size);
    txString.push_back(command);
    txString.push_back(address);
    txString.push_back(length);
    txString.push_back(id1);
    txString.push_back(data1[0]);
    txString.push_back(id2);
    txString.push_back(data2[0]);

    checksum = id + size + command + address + length + id1 + data1[0] + id2 + data2[0];
    checksum = (checksum & 0x000000ff)^ 0x000000ff;
    txString.push_back(checksum);
    serial->Write(txString);
}
