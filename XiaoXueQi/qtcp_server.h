#ifndef QTCP_SERVER_H
#define QTCP_SERVER_H

#include<QObject>
#include<QHostAddress>
#include<QHostInfo>
#include<QDebug>
#include<QStringList>
#include<QTcpServer>
#include<QTcpSocket>

class QTCP_server : public QObject
{
    Q_OBJECT
public:
    static QTCP_server* gethand(){
        if(tcpServer==nullptr)
            tcpServer=new QTCP_server();
        return tcpServer;
    }
    void getNetWorkInfo();
    QStringList iplist;

    void startServer(QString ipAdd);
    void stopServer();
signals:

private slots:void slot_getadd(QHostInfo info);

private:
    explicit QTCP_server(QObject *parent=nullptr);
    static QTCP_server*tcpServer;//静态类 这里的定义只是意思意思 要在类的外部定义。
    QHostInfo hostinfo;
    QHostAddress hostadd;
    QList<QHostAddress> hostaddlist;

    QTcpServer* tcp_server;
    QList<QTcpSocket> tcp_socketlist;

};

#endif // QTCP_SERVER_H
