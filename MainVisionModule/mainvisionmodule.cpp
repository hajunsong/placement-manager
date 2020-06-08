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
    listenSockFD = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(listenSockFD < 0){
        cout << endl << "[MVM]socket create error" << endl;
    }

    int on = 1;
    if(setsockopt(listenSockFD, SOL_SOCKET, SO_REUSEADDR, reinterpret_cast<const char*>(&on), sizeof(on)) < 0){
        cout << endl << "[MVM]set option curLen = 0; error!!" << endl;
    }

    server_addr.sin_addr.s_addr = inet_addr(dataControl->TCP_ADDRESS.c_str());
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);

    if(bind(listenSockFD, reinterpret_cast<struct sockaddr*>(&server_addr), sizeof(server_addr)) < 0){
        cout << endl << "[MVM]bind error" << endl;
    }

    while(true){
        pthread_create(&comm_rx, nullptr, comm_rx_func, this);
        pthread_join(comm_rx, nullptr);
        shutdown(clientSockFD, SHUT_RDWR);
        usleep(1000000);
    }
}

void *MainVisionModule::comm_rx_func(void *arg)
{
    MainVisionModule* pThis = static_cast<MainVisionModule*>(arg);

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
            pThis->dataControl->receive_flag = false;
            pThis->comm_thread_rx_run = false;
        }
        if(pThis->byteLen > 0){
//            cout << pThis->buf << endl;

            pThis->jsonDocument.ParseInsitu(pThis->buf);
            pThis->orderMsg = pThis->jsonDocument["order"].GetString();

            pThis->dataControl->orderMsg = pThis->orderMsg;
            pThis->dataControl->logger->write("Order Msg : " + pThis->dataControl->orderMsg);
            cout << "Order Msg ; " << pThis->dataControl->orderMsg << endl;

            pThis->dataControl->receive_flag = true;
        }
    }
    cout << "Finish RX Thread Main Vision Module" << endl;
    pThis->dataControl->logger->write("Finish RX Thread Main Vision Module");

    pThis->comm_thread_tx_run = false;
    pthread_join(pThis->comm_tx, nullptr);

    return nullptr;
}

void *MainVisionModule::comm_tx_func(void *arg)
{
    MainVisionModule* pThis = static_cast<MainVisionModule*>(arg);
    while(!pThis->comm_thread_rx_run){
        usleep(1000);
    }

    pThis->comm_thread_tx_run = true;
    int cnt = -1;
    clock_t t1 = 0;
    while(pThis->comm_thread_tx_run){
        cout << (double)((clock() - t1)/1000) << endl;
        t1 = clock();
        cnt++;
        usleep(100000);

        StringBuffer s;
        Writer<StringBuffer> writer(s);

        writer.StartObject();
        writer.Key("order");
        writer.String("sendstate");
        writer.Key("state");
        writer.StartObject();
        writer.Key("drop");
        writer.StartArray();
        writer.Bool(pThis->dataControl->dropping);
        writer.EndArray();
        writer.Key("repicking");
        writer.StartArray();
        writer.Bool(pThis->dataControl->state_state == 'O' ? true : false);
        writer.StartArray();
        writer.Double(pThis->dataControl->x_offset);
        writer.Double(pThis->dataControl->y_offset);
        writer.Double(0);
        writer.Double(pThis->dataControl->rotation_offset);
        writer.EndArray();
        writer.EndArray();
        writer.EndObject();
        writer.EndObject();

//        cout << s.GetString() << endl;

        if (pThis->comm_thread_tx_run){
            pThis->len = s.GetLength();
            stringstream tmp;
            tmp.width(16);
            tmp.setf(ios_base::left);
            tmp << pThis->len;
            pThis->sendByteLen = send(pThis->clientSockFD, tmp.str().c_str(), 16, 0);
            if(pThis->sendByteLen < 0){
                cout << endl << "[MVM]Send Error" << endl;
                pThis->dataControl->logger->write("[MVM]Send Error");
                pThis->comm_thread_tx_run = false;
            }

            memset(pThis->bufSend, 0, MAXSENDBUFSIZE);
            strcpy(pThis->bufSend, s.GetString());
            pThis->sendByteLen = send(pThis->clientSockFD, pThis->bufSend, static_cast<size_t>(pThis->len), 0);

            if(pThis->sendByteLen < 0){
                cout << endl << "[MVM]Send Error" << endl;
                pThis->dataControl->logger->write("[MVM]Send Error");
                pThis->comm_thread_tx_run = false;
            }

            cout << endl << "Send data size : " << pThis->sendByteLen << endl;
            cout << "Send data : " << pThis->bufSend << endl;

            pThis->dataControl->logger->write("Send data size : " + to_string(pThis->len));
            pThis->msg = "";
            pThis->msg.append("Send data : ");
            pThis->msg.append(s.GetString());
            pThis->dataControl->logger->write(pThis->msg);
        }
    }
    cout << "Finish TX Thread Main Vision Module" << endl;
    pThis->dataControl->logger->write("Finish TX Thread Main Vision Module");

    return nullptr;
}

void MainVisionModule::stop(){
    cout << "Stop Main Vision Module Comm" << endl;
    comm_thread_rx_run = false;
    pthread_join(comm_rx, nullptr);
}
