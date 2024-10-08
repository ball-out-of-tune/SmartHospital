#include <cstdio>

#include "ServerSocketThread.h"
#include "NetUtils.h"

ServerSocketThread::ServerSocketThread(qintptr descriptor){
    socketDescripter=descriptor;
    buffer = QString();
    alive=true;

    socket=new QTcpSocket();
    socket->setSocketDescriptor(socketDescripter);
    qDebug("ServerSocket connected from:%s",socket->peerAddress().toString().toStdString().data());
    socket->write(NetUtils::wrapMessage("ping"));

    connect(socket,SIGNAL(readyRead()),this,SLOT(readyRead_slot()));
    connect(this,SIGNAL(toDoPing()),this,SLOT(doPing_slot()));
}

ServerSocketThread::~ServerSocketThread(){
    socket->close();
    delete socket;
}

void ServerSocketThread::run(){
    while (true) {
        msleep(NetUtils::waitTime);
        if(!hasReply){
            qDebug("Client No-reply For more than %ld ms,disconnected!",NetUtils::waitTime);
            socket->disconnectFromHost();
            socket->waitForDisconnected();
            alive=false;
        }
        emit toDoPing();
        hasReply=false;
    }
}

void ServerSocketThread::doPing_slot(){
    socket->write(NetUtils::wrapMessage("ping"));
}

void ServerSocketThread::readyRead_slot(){
    buffer+=socket->readAll();
    int pre=buffer.indexOf(NetUtils::messagePrefix);
    if(pre>=0){
        buffer=buffer.mid(pre);
        int suff=buffer.indexOf(NetUtils::messageSuffix);
        if(suff>0){
            doCommand(
                        buffer.mid(
                            NetUtils::messagePrefix.length()
                            ,suff-NetUtils::messagePrefix.length()));
            buffer=buffer.mid(suff);
        }
    }
}

void ServerSocketThread::doCommand(QString str){
    hasReply=true;
    qDebug("Server Taken:%s",str.toStdString().data());
}
