#include "qtcp_server.h"
QTCP_server* QTCP_server::tcpServer = nullptr;
QTCP_server::QTCP_server(QObject *parent):QObject(parent)
{
    qDebug()<<hostinfo.localHostName();
    hostinfo.setHostName(hostinfo.localHostName());
}
void QTCP_server::getNetWorkInfo(){
    QHostInfo::lookupHost(hostinfo.localHostName(),this,SLOT(slot_getadd(QHostInfo)));
}

void QTCP_server::slot_getadd(QHostInfo info){
    hostaddlist=info.addresses();
    if (hostaddlist.count()>0){
        for(int i=0;i<hostaddlist.count();i++){
            iplist.append((hostaddlist.at(i).toString()));
        }
    }

}

void QTCP_server::startServer(QString ipAdd){
    tcp_server = new QTcpServer();
    if (tcp_server->listen(QHostAddress::Any,6655))
        qDebug()<<"server starts OK";
}

void QTCP_server::stopServer(){
    tcp_server->close();
}
