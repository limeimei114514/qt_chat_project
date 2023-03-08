#include "mytcpserver.h"
#include <string>
#include <QDateTime>
#include"mysql.h"
extern QString NAME;
MyTCPServer* MyTCPServer::tcpserverhand=nullptr;
MyTCPServer::MyTCPServer(QObject *parent):QObject(parent)
{
    qDebug()<<"This PCs name is :"<<hostInfo.localHostName();
    for(int i=0;i<SOCKET_NUMBER;i++)
    {
        clientList.append(new QTcpSocket);
    }
    hostInfo.setHostName(hostInfo.localHostName());
    hostInfo.lookupHost(hostInfo.localHostName(),this,SLOT(slot_getaddress(QHostInfo)));

}
void MyTCPServer::slot_getaddress(QHostInfo info){
    emit sig_getIPaddresses(info);
    MyTCPServer *tcp= MyTCPServer::gethand();
    tcp->hostaddlist=info.addresses();
    if (hostaddlist.count()>0){
        for(int i=0;i<hostaddlist.count();i++){
            iplist.append((hostaddlist.at(i).toString()));
        }
    }
}
int MyTCPServer:: clientcount(bool* flag)
{
    int sum=0;
    for(int i=0;i<SOCKET_NUMBER;i++)
    {
        sum+=flag[i];

    }
    return sum;
}
void MyTCPServer::slot_newconnect(){
    qDebug()<<"噫！好我中了！";
    int socketIndex=0;
    for (int i=0;i<MyTCPServer::SOCKET_NUMBER+1;i++){
        if(!this->socketFlag[i]){
            socketIndex=i;
            break;
        }
        if (i==SOCKET_NUMBER){
            qDebug()<<"服务器人满为患了";
            return;
        }

    }
    socketFlag[socketIndex]=true;
    //clientList.append(tcp_server.nextPendingConnection());
   clientList[socketIndex]=(tcp_server.nextPendingConnection());

    connect(clientList.at(socketIndex),SIGNAL(readyRead()),this,SLOT(slot_readData()));
    connect(clientList.at(socketIndex),SIGNAL(disconnected()),this,SLOT(slot_disconnect()));

    qDebug()<<clientList[socketIndex]->IPv4Protocol;
    QString ip= clientList[socketIndex]->peerAddress().toString();
    qDebug()<<"The Guest's IP is : "<<ip;
}

bool MyTCPServer::openTCPserver(QString ip,QString port){
    QHostAddress hostadd;

    hostadd.setAddress(ip);

    if (tcp_server.listen(hostadd,port.toInt())){
        emit serverStart();
        connect(&tcp_server,SIGNAL(newConnection()),this,SLOT(slot_newconnect()));//这一步将socket和server相连接

    }
    else return false;

    return true;
}

bool MyTCPServer::shutdownTCPserver(){
    emit serverShutdown();
    return true;
}

void MyTCPServer::slot_readData(){

    tcp_socket = (QTcpSocket*)sender();
    QByteArray databyte = tcp_socket->readAll();

    QString str = QString::fromStdString(databyte.toStdString());
   qDebug()<<str;
    //
     QString usernameorID;
     QString password;
    if(str.mid(0,1).toInt()==1||str.mid(0,1).toInt()==2)
   { bool ok;
    int length=str.mid(1,2).toInt(&ok,10);
     usernameorID=str.mid(3,length),password=str.mid(length+3);
   }

    switch (str.mid(0,1).toInt()) {

    case 1:
        //注册
    {
        MySQL* sqlhand=MySQL::gethand();
        sqlhand->openDatabase();
        qDebug()<<"aaa";
        idxh=sqlhand->seekData().toLong();
        idxh=idxh+1;
        qDebug()<<"bbb";
        sqlhand->insertData(usernameorID,password,QString::number(idxh));
        QString id = QString::number(idxh, 10); //将数字id转为字符串
        QString str1="1"+id;//返回开头1代表返回注册后的id
        qDebug()<<str1;
        tcp_socket->write(str1.toUtf8());//传回id
        break;
    }
    case 2:
        //登录
    {
        MySQL* sqlhand=MySQL::gethand();
        sqlhand->openDatabase();
        qDebug()<<"ccc";
        QString name=sqlhand->selectData(usernameorID,password);

        qDebug()<<"ddd";
        if(name!="")//selectData返回string类型，如果select成功返回用户名 不成功返回error
           { int l=name.length();
            QString tmpstr;
            if(l<9){
                tmpstr=QString::number(0)+QString::number(l);
            }
            else tmpstr=QString::number(l);
            QString str2="2"+tmpstr+name;//返回开头2代表返回 登陆成功后的用户名
            tcp_socket->write(str2.toStdString().data());
            for(int i=0;i<clientList.count();i++)
            { QTcpSocket *item = clientList.at(i);

                QString str6="6"+name+"加入了聊天。当前聊天室共"+QString::number(clientcount(socketFlag))+"人。";

              item->write(str6.toUtf8());
            }
            }



        else
           { tcp_socket->write("3");//返回3代表用户名 密码错误
            qDebug()<<"eee";}
        break;
    }
    case 3:
        //客户端发送消息到服务端
    {
        emit serverNewMessage(str.mid(1));

        qDebug()<<"ff";

        for(int i=0;i<clientList.count();i++)
        {
            QTcpSocket *item = clientList.at(i);
            QDateTime *datatime=new QDateTime(QDateTime::currentDateTime());
            QString strtime = datatime->toString("yyyy-MM-dd hh:mm:ss ddd");    //设置时间格式

            QString str4="4"+strtime+"\n"+str.mid(1)+"\n";
            item->write(str4.toUtf8()); //返回开头4代表服务器向用户端发送聊天信息
        }
        break;
    }
    default:
        qDebug()<<str;
    }

    //



}

void MyTCPServer::slot_disconnect(){
    tcp_socket = (QTcpSocket*)sender();
        for (int i=0;i<SOCKET_NUMBER;i++){
            if (clientList.at(i)->peerAddress()==tcp_socket->peerAddress()){
                clientList[i]=new QTcpSocket;
                socketFlag[i]=false;
                return;
            }
        }
        qDebug()<<"Delete client error!";
        //tcp_socket->peerAddress();
        return;
}
