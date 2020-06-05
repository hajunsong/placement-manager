#include "mainvisionmodule.h"

MainVisionModule::MainVisionModule(void *arg, uint16_t portNum)
{
    dataControl = static_cast<DataControl*>(arg);

    comm_thread_rx_run = false;
    comm_thread_tx_run = false;

    port = portNum;
}

MainVisionModule::~MainVisionModule(){
    stop();
    usleep(10000);
}

void MainVisionModule::start(){
    pthread_create(&comm_rx, nullptr, comm_rx_func, this);
}

void *MainVisionModule::comm_rx_func(void *arg)
{
    MainVisionModule* pThis = static_cast<MainVisionModule*>(arg);

    pThis->listenSockFD = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(pThis->listenSockFD < 0){
        cout << endl << "[MVM]socket create error" << endl;
    }

    int on = 1;
    if(setsockopt(pThis->listenSockFD, SOL_SOCKET, SO_REUSEADDR, reinterpret_cast<const char*>(&on), sizeof(on)) < 0){
        cout << endl << "[MVM]set option curLen = 0; error!!" << endl;
    }

    pThis->server_addr.sin_addr.s_addr = inet_addr("192.168.0.123");
    pThis->server_addr.sin_family = AF_INET;
    pThis->server_addr.sin_port = htons(pThis->port);

    if(bind(pThis->listenSockFD, reinterpret_cast<struct sockaddr*>(&pThis->server_addr), sizeof(server_addr)) < 0){
        cout << endl << "[MVM]bind error" << endl;
    }

    cout << "[MVM]server running waiting. Waiting client..." << endl;

    if(listen(pThis->listenSockFD, MAXCONNECTIONS) < 0){
        cout << endl << "[MVM]listen error" << endl;
    }

    int clientAddrSize = sizeof(client_addr);

    pThis->curLen = 0;
    memset(pThis->bufWait, 0, MAXWAITBUFSIZE);
    pThis->ptrRecvBufIndx = pThis->bufWait;
    pThis->clientSockFD = accept(pThis->listenSockFD, reinterpret_cast<struct sockaddr*>(&pThis->client_addr), reinterpret_cast<socklen_t*>(&clientAddrSize));

    if(pThis->clientSockFD < 0){
        cout << endl << "[MVM]accept error" << endl;
    }

    cout << endl << "[MVM]client accepted" << endl;
    cout << "[MVM]address : " << inet_ntoa(pThis->client_addr.sin_addr) << endl;
    cout << "[MVM]port : " << ntohs(pThis->client_addr.sin_port) << endl;

    pthread_create(&pThis->comm_tx, nullptr, comm_tx_func, pThis);

    pThis->comm_thread_rx_run = true;

    while(pThis->comm_thread_rx_run){
        usleep(100000);
        memset(pThis->buf, 0, 16);
        recv(pThis->clientSockFD, pThis->buf, 16, 0);
        pThis->dataLen = atoi(pThis->buf);

        memset(pThis->buf, 0, MAXRECEIVEBUFSIZE);
        pThis->byteLen = recv(pThis->clientSockFD, pThis->buf, static_cast<size_t>(pThis->dataLen), 0);

        if(pThis->byteLen == 0 || pThis->byteLen > MAXRECEIVEBUFSIZE){
            cout << endl << "[MVM]client" << inet_ntoa(pThis->client_addr.sin_addr) << "closed." << endl;
            close(pThis->clientSockFD);
            break;
        }
        if(pThis->byteLen > 0){
//            cout << pThis->buf << endl;
            pThis->jsonObjRecv = QJsonDocument::fromJson(pThis->buf).object();
            pThis->orderMsg = pThis->jsonObjRecv["order"].toString();
//            qDebug() << pThis->orderMsg;
            pThis->dataControl->orderMsg = pThis->orderMsg;
            pThis->dataControl->logger->write("Order Msg : " + pThis->dataControl->orderMsg.toStdString());

            pThis->dataControl->receive_flag = true;

//            QJsonArray jsonArrayDrop;
//            jsonArrayDrop.push_back(pThis->dataControl->dropping);

//            QJsonArray jsonArrayOffset;
//            jsonArrayOffset.push_back(pThis->dataControl->state_state == 'O' ? true : false);
//            jsonArrayOffset.push_back(pThis->dataControl->x_offset);
//            jsonArrayOffset.push_back(pThis->dataControl->y_offset);
//            jsonArrayOffset.push_back(0);
//            jsonArrayOffset.push_back(pThis->dataControl->rotation_offset);

//            QJsonObject jsonObjState;
//            jsonObjState.insert("drop", jsonArrayDrop);
//            jsonObjState.insert("repicking", jsonArrayOffset);

//            QJsonObject jsonObjSend;
//            jsonObjSend.insert("order", QJsonValue::fromVariant("sendstate"));
//            jsonObjSend.insert("state", jsonObjState);

//            QJsonDocument jsonDocSend(jsonObjSend);
//            QByteArray sendData = jsonDocSend.toJson().simplified().replace("{ ", "{").replace("[ ","[").replace(" ]","]").replace(" }", "}").replace("]}}", "]]}}").replace("false, ","false, [");

//            pThis->sendByteLen = sendData.length();
//            send(pThis->clientSockFD, QString::number(pThis->sendByteLen).leftJustified(16).toStdString().c_str(), 16, 0);

//            memset(pThis->bufSend, 0, MAXSENDBUFSIZE);
//            strcpy(pThis->bufSend, sendData);
//            pThis->sendByteLen = send(pThis->clientSockFD, pThis->bufSend, static_cast<size_t>(pThis->sendByteLen), 0);

//            cout << endl << "Send data size : " << pThis->sendByteLen << endl;
//            cout << "Send data : " << pThis->bufSend << endl;
        }
    }
    cout << "Finish Thread Main Vision Module" << endl;
    pThis->dataControl->logger->write("Finish Thread Main Vision Module");

    return nullptr;
}

void *MainVisionModule::comm_tx_func(void *arg)
{
    MainVisionModule* pThis = static_cast<MainVisionModule*>(arg);
    pThis->comm_thread_tx_run = true;
    int cnt = -1;
    clock_t t1 = 0;
    while(pThis->comm_thread_tx_run){
        cout << (double)((clock() - t1)/1000) << endl;
        t1 = clock();
        cnt++;
        usleep(100000);
        QJsonArray jsonArrayDrop;
        jsonArrayDrop.push_back(pThis->dataControl->dropping);

        QJsonArray jsonArrayRepickin, jsonArrayOffset;
        jsonArrayOffset.push_back(pThis->dataControl->x_offset);
        jsonArrayOffset.push_back(pThis->dataControl->y_offset);
        jsonArrayOffset.push_back(0);
        jsonArrayOffset.push_back(pThis->dataControl->rotation_offset);
        jsonArrayRepickin.push_back(pThis->dataControl->state_state == 'O' ? true : false);
        jsonArrayRepickin.push_back(jsonArrayOffset);

        QJsonObject jsonObjState;
        jsonObjState.insert("drop", jsonArrayDrop);
        jsonObjState.insert("repicking", jsonArrayRepickin);

        QJsonObject jsonObjSend;
        jsonObjSend.insert("order", QJsonValue::fromVariant("sendstate"));
        jsonObjSend.insert("state", jsonObjState);

        QJsonDocument jsonDocSend(jsonObjSend);
        QByteArray sendData = jsonDocSend.toJson(QJsonDocument::Compact);

        pThis->sendByteLen = sendData.length();
        send(pThis->clientSockFD, QString::number(pThis->sendByteLen).leftJustified(16).toStdString().c_str(), 16, 0);

        memset(pThis->bufSend, 0, MAXSENDBUFSIZE);
        strcpy(pThis->bufSend, sendData);
        pThis->sendByteLen = send(pThis->clientSockFD, pThis->bufSend, static_cast<size_t>(pThis->sendByteLen), 0);

        if(pThis->sendByteLen < 0){
            cout << endl << "[MVM]Send Error" << endl;
            pThis->dataControl->logger->write("[MVM]Send Error");
            pThis->restart();
        }

        cout << endl << "Send data size : " << pThis->sendByteLen << endl;
        cout << "Send data : " << pThis->bufSend << endl;

        pThis->dataControl->logger->write("Send data size : " + QString::number(pThis->sendByteLen).toStdString());
        pThis->dataControl->logger->write("Send data : " + sendData.toStdString());
    }

    return nullptr;
}

void MainVisionModule::stop(){
    cout << "Stop Main Vision Module Comm" << endl;
    close(clientSockFD);
    comm_thread_rx_run = false;
    comm_thread_tx_run = false;
    pthread_join(comm_rx, nullptr);
    pthread_join(comm_tx, nullptr);
}

void MainVisionModule::restart(){
    cout << "Restart Main Vison Module Comm" << endl;
    stop();
    start();
}
