#include "placevisionmodule.h"

PlaceVisionModule::PlaceVisionModule(void *arg, uint16_t portNum)
{
    dataControl = static_cast<DataControl*>(arg);

    strcpy(bufSend, "VT1*");

    comm_thread_rx_run = false;
    comm_thread_tx_run = false;

    port = portNum;
}

PlaceVisionModule::~PlaceVisionModule(){
    stop();
    usleep(10000);
}

void PlaceVisionModule::start(){
    listenSockFD = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(listenSockFD < 0){
        cout << endl << "[PVM]socket create error" << endl;
    }

    int on = 1;
    if(setsockopt(listenSockFD, SOL_SOCKET, SO_REUSEADDR, reinterpret_cast<const char*>(&on), sizeof(on)) < 0){
        cout << endl << "[PVM]set option curLen = 0; error!!" << endl;
    }

    server_addr.sin_addr.s_addr = inet_addr(dataControl->TCP_ADDRESS.c_str());
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);

    if(bind(listenSockFD, reinterpret_cast<struct sockaddr*>(&server_addr), sizeof(server_addr)) < 0){
        cout << endl << "[PVM]bind error" << endl;
    }

    while(true){
        pthread_create(&comm_rx, nullptr, comm_rx_func, this);
        pthread_join(comm_rx, nullptr);
        usleep(1000000);
    }
}

void *PlaceVisionModule::comm_rx_func(void *arg)
{
    PlaceVisionModule* pThis = static_cast<PlaceVisionModule*>(arg);

    cout << "[PVM]server running waiting. Waiting client..." << endl;

    if(listen(pThis->listenSockFD, MAXCONNECTIONS) < 0){
        cout << endl << "[PVM]listen error" << endl;
    }

    int clientAddrSize = sizeof(client_addr);

    pThis->curLen = 0;
    memset(pThis->bufWait, 0, MAXWAITBUFSIZE);
    pThis->ptrRecvBufIndx = pThis->bufWait;
    pThis->clientSockFD = accept(pThis->listenSockFD, reinterpret_cast<struct sockaddr*>(&pThis->client_addr), reinterpret_cast<socklen_t*>(&clientAddrSize));

    if(pThis->clientSockFD < 0){
        cout << endl << "[PVM]accept error" << endl;
    }

    cout << endl << "[PVM]client accepted" << endl;
    cout << "[PVM]address : " << inet_ntoa(pThis->client_addr.sin_addr) << endl;
    cout << "[PVM]port : " << ntohs(pThis->client_addr.sin_port) << endl;

    pThis->sendByteLen = send(pThis->clientSockFD, pThis->bufSend, sizeof(bufSend), 0);

    pThis->comm_thread_rx_run = true;

    while(pThis->comm_thread_rx_run){
        usleep(100);

        memset(pThis->buf, 0, MAXRECEIVEBUFSIZE);
        pThis->byteLen = recv(pThis->clientSockFD, pThis->buf, 47, 0);

        if(pThis->byteLen == 0 || pThis->byteLen > MAXRECEIVEBUFSIZE){
            cout << endl << "[PVM]client" << inet_ntoa(pThis->client_addr.sin_addr) << "closed." << endl;
            shutdown(pThis->clientSockFD, SHUT_RDWR);
            pthread_exit(nullptr);
        }
        if(pThis->byteLen > 0){
//            cout << pThis->buf << endl;
            char dataBuf[7];

            pThis->dataControl->state_state = pThis->buf[2];
            pThis->dataControl->r_state_state = pThis->buf[25];

            if(pThis->dataControl->state_state == 'O'){
                pThis->dataControl->repicking_object = true;
            }
            else{
                pThis->dataControl->repicking_object = false;
            }

            memcpy(dataBuf, pThis->buf + 4, 6);
            pThis->dataControl->i_x_offset = atoi(dataBuf);
            if(pThis->buf[3] == 'M'){
                pThis->dataControl->x_offset = (-1)*static_cast<double>(pThis->dataControl->i_x_offset/1000.0);
            }
            else{
                pThis->dataControl->x_offset = static_cast<double>(pThis->dataControl->i_x_offset/1000.0);
            }

            memcpy(dataBuf, pThis->buf + 11, 6);
            pThis->dataControl->i_y_offset = atoi(dataBuf);
            if(pThis->buf[10] == 'M'){
                pThis->dataControl->y_offset = (-1)*static_cast<double>(pThis->dataControl->i_y_offset/1000.0);
            }
            else{
                pThis->dataControl->y_offset = static_cast<double>(pThis->dataControl->i_y_offset/1000.0);
            }

            memcpy(dataBuf, pThis->buf + 17, 6);
            pThis->dataControl->i_rotation_offset = atoi(dataBuf);
            pThis->dataControl->rotation_offset = (-1)*static_cast<double>(pThis->dataControl->i_rotation_offset);

            memcpy(dataBuf, pThis->buf + 27, 6);
            pThis->dataControl->i_r_x_offset = atoi(dataBuf);
            if(pThis->buf[26] == 'M'){
                pThis->dataControl->r_x_offset = (-1)*static_cast<double>(pThis->dataControl->i_r_x_offset/1000.0);
            }
            else{
                pThis->dataControl->r_x_offset = static_cast<double>(pThis->dataControl->i_r_x_offset/1000.0);
            }

            memcpy(dataBuf, pThis->buf + 34, 6);
            pThis->dataControl->i_r_y_offset = atoi(dataBuf);
            if(pThis->buf[33] == 'M'){
                pThis->dataControl->r_y_offset = (-1)*static_cast<double>(pThis->dataControl->i_r_y_offset/1000.0);
            }
            else{
                pThis->dataControl->r_y_offset = static_cast<double>(pThis->dataControl->i_r_y_offset/1000.0);
            }

            memcpy(dataBuf, pThis->buf + 40, 6);
            pThis->dataControl->i_r_rotation_offset = atoi(dataBuf);
            pThis->dataControl->r_rotation_offset = (-1)*static_cast<double>(pThis->dataControl->i_r_rotation_offset);

            printf("\n");
            printf("[offset]x:=%.3f\t y:=%.3f\t r:=%.3f\n", pThis->dataControl->x_offset, pThis->dataControl->y_offset, pThis->dataControl->rotation_offset);
            printf("repicking object : %s\n", pThis->dataControl->repicking_object == true ? "true" : "false");
//            printf("[r_offset]x:=%3.4f\t y:=%3.4f\t r:=%3.4f\n", pThis->dataControl->r_x_offset, pThis->dataControl->r_y_offset, pThis->dataControl->r_rotation_offset);

            pThis->dataControl->logger->write("[offset] x:=" + to_string(pThis->dataControl->x_offset) +
                                              ",y:=" + to_string(pThis->dataControl->y_offset) + ",z:=" + to_string(pThis->dataControl->rotation_offset));
            pThis->dataControl->logger->write("repicking object : " + to_string(pThis->dataControl->repicking_object));
        }
    }
    cout << "Finish Thread Place Vision Module" << endl;

    return nullptr;
}

void *PlaceVisionModule::comm_tx_func(void *arg)
{
    PlaceVisionModule* pThis = static_cast<PlaceVisionModule*>(arg);
    pThis->comm_thread_tx_run = true;

    return nullptr;
}

void PlaceVisionModule::stop(){
    cout << "Stop Place Vision Module Comm" << endl;
    comm_thread_rx_run = false;
    comm_thread_tx_run = false;
    pthread_join(comm_rx, nullptr);
    pthread_join(comm_tx, nullptr);
}
