#ifndef MYTCPSERVER_H
#define MYTCPSERVER_H

#include <QObject>
#include <QHostAddress>
#include <QHostInfo>
#include <QDebug>
#include <QStringList>
#include <QTcpServer>
#include <QTcpSocket>
#include <string>

class MyTCPServer : public QObject
{
    Q_OBJECT
public:
    static MyTCPServer*gethand(){
        if (tcpserverhand==nullptr)
            tcpserverhand= new MyTCPServer();
        return tcpserverhand;
    }
    bool openTCPserver(QString,QString);
    bool shutdownTCPserver();
    QStringList iplist;
    const int SOCKET_NUMBER=64;
private:
    explicit MyTCPServer(QObject *parent = nullptr);
    static MyTCPServer* tcpserverhand;
    QHostInfo hostInfo;
    QHostAddress hostadd;
    QTcpServer tcp_server;
    QTcpSocket *tcp_socket;
    QList<QString>  usernameList;
    QList<QHostAddress> hostaddlist;
    QList<QTcpSocket*> clientList;
    bool socketFlag[64]={false};
    long idxh=0;
    QString NAME;
    int  clientcount(bool* flag);
private slots://槽是有返回值的 定义了必须得实现 必须要写void 是一个函数
    void slot_newconnect();
    void slot_getaddress(QHostInfo info);
    void slot_readData();
    void slot_disconnect();
signals:
    void serverStart();
    void serverShutdown();
    void sig_getIPaddresses(QHostInfo info);
    void serverNewMessage(QString);
};

#endif // MYTCPSERVER_H
